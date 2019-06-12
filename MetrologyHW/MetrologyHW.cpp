#include "MetrologyHW.h"
#include <qfiledialog.h>
#include <fstream>
#include <math.h>
#include <string>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/erf.hpp>

using namespace boost;
using namespace math;

MetrologyHW::MetrologyHW(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	for (int i = 0; i < 8; ++i)
	{
		lableArr[i].setParent(this);
	}
	for (int i = 0; i < 6; ++i)
	{
		lableArr[i].setStyleSheet(tr("border: 1px solid black;"));
		lableArr[i].setGeometry(i % 2 * 410, 100 + int(i / 2) * 65, 400, 60);
	}

	setFixedHeight(300);
	setFixedWidth(1000);


	startBtn.setParent(this);
	startBtn.setGeometry(810, 100, 190, 190);
	startBtn.setText(tr("Start"));
	startBtn.setStyleSheet(tr("background-color: red; border: 2px solid black;"));

	lableArr[6].setGeometry(0, 20, 150, 20);
	lableArr[7].setGeometry(0, 60, 150, 20);
	lableArr[6].setText(tr("Файл входных данных"));
	lableArr[7].setText(tr("Файл выходных данных"));

	fileInPath.setParent(this);
	fileOutPath.setParent(this);
	fileInPath.setGeometry(150, 20, 750, 20);
	fileOutPath.setGeometry(150, 60, 750, 20);

	browseFileIn.setParent(this);
	browseFileOut.setParent(this);
	browseFileIn.setGeometry(900, 20, 100, 20);
	browseFileOut.setGeometry(900, 60, 100, 20);
	browseFileIn.setText(tr("Выбрать файл"));
	browseFileOut.setText(tr("Выбрать файл"));

	lableArr[0].setText(tr("Количество элементов: "));
	lableArr[1].setText(tr("Мат. ожидание: "));
	lableArr[2].setText(tr("Дисперсия: "));
	lableArr[3].setText(tr("Хи-квадрат наблюдаемое: "));
	lableArr[4].setText(tr("p-value: "));
	lableArr[5].setText(tr("Вывод: "));

	connect(&startBtn, &QPushButton::clicked, this, &MetrologyHW::on_startBtn_clicked);
	connect(&browseFileIn, &QPushButton::clicked, this, &MetrologyHW::on_browseFileIn_clicked);
	connect(&browseFileOut, &QPushButton::clicked, this, &MetrologyHW::on_browseFileOut_clicked);
}

double MetrologyHW::normF(double _x, double _m, double _d)
{
	return 0.5 * (1 + erf((_x - _m) / (sqrt(2 * _d))));
}

void MetrologyHW::on_browseFileOut_clicked()
{
	fileOutName = QFileDialog::getOpenFileName(this,
		tr("Open File"), "/home/", tr("Image Files (*.txt)"));
	fileOutPath.setText(fileOutName);
}

void MetrologyHW::on_browseFileIn_clicked()
{
	fileInName = QFileDialog::getOpenFileName(this,
		tr("Open File"), "/home/", tr("Image Files (*.txt)"));
	fileInPath.setText(fileInName);
}

void MetrologyHW::on_startBtn_clicked()
{
	if (fileInPath.text() == "" || fileOutPath.text() == "")
		return;

	fileInName = fileInPath.text();
	fileOutName = fileOutPath.text();

	ifstream fin;
	fin.open(fileInName.toStdString());
	if (fin.eof())
		return;

	vector<double> v;
	double x, step, xsum = 0, xmean, xvar;

	while (!fin.eof())
	{
		fin >> x;
		v.push_back(x);
	}



	int n = ceil(sqrt(v.size()));
	sort(v.begin(), v.end());

	step = (v[v.size() - 1] - v[0]) / n;

	for (auto i : v)
		xsum += i;

	xmean = xsum / v.size();
	xsum = 0;

	for (auto i : v)
		xsum += i * i;

	xvar = xsum / v.size() - xmean * xmean;

	if (xvar == 0)
		return;

	vector<double> p0(1, 0);

	for (auto i : v)
	{
		if (i <= v[0] + step * p0.size())
			p0[p0.size() - 1]++;
		else
			p0.push_back(1);
	}

	for (int i = 0; i < p0.size(); ++i)
		p0[i] /= v.size();

	double xe = 0;

	for (int i = 0; i < n; i++)
	{
		double p;
		if (i == 0)
			p = (normF(v[0] + step * i + step, xmean, xvar));
		else if (i == n - 1)
			p = 1 - normF(v[0] + step * i, xmean, xvar);
		else
			p = normF(v[0] + step * i + step, xmean, xvar) - normF(v[0] + step * i, xmean, xvar);

		xe += v.size() / p * pow(p0[i] - p, 2);
	}


	double pValue;
	pValue = 1 - gamma_p(n / 2, xe / 2);



	lableArr[0].setText(trUtf8("Количество элементов: ") + QString::number(v.size()));
	lableArr[1].setText(trUtf8("Мат. ожидание: ") + QString::number(xmean));
	lableArr[2].setText(trUtf8("Дисперсия: ") + QString::number(xvar));
	lableArr[3].setText(trUtf8("Хи-квадрат наблюдаемое: ") + QString::number(xe));
	lableArr[4].setText(trUtf8("p-value: ") + QString::number(pValue));
	if (pValue >= 0.05)
		lableArr[5].setText(trUtf8("Вывод: p-value >= 0.05 => Распределение нормальное"));
	else
		lableArr[5].setText(trUtf8("Вывод: p-value < 0.05 => Распределение не нормальное"));

	ofstream fout;
	fout.open(fileOutName.toStdString());
	string s = "";
	s += "Исходные данные: " + fileInName.toStdString() + "\n";
	s += "Количество элементов: \t\t\t" + to_string(v.size()) + "\n";
	s += "Мат. ожидание: \t\t\t\t" + to_string(xmean) + "\n";
	s += "Дисперсия: \t\t\t\t" + to_string(xvar) + "\n";
	s += "Хи-квадрат наблюдаемое: \t\t" + to_string(xe) + "\n";
	s += "p-value: \t\t\t\t" + to_string(pValue) + "\n";
	if (pValue >= 0.05)
		s += "Вывод: p-value >= 0.05 => Распределение нормальное";
	else
		s += "Вывод: p-value < 0.05 => Распределение не нормальное";

	fout << s;
	fout.close();
}