#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <iterator>
#include <fstream>
using namespace std;
double x, y, z = 0.;
double R = 1.;
void defineCoordinates(vector <double>& coordinates, double a, double b, int parts) {
	coordinates[0] = a;
	coordinates[coordinates.size() - 1] = b;
	for(int i = 1; i < parts; i++) {
		coordinates[i] = coordinates[i - 1] + (b - a) / parts;
	}
}
vector<double> resizeCoordinates(vector<double> coordinates, double a, double b, int amount) {
	vector<double> finalCoordinates(amount);
	for (int i = 0; i < finalCoordinates.size(); i++) {
		finalCoordinates[i] = coordinates[i] * (b - a) / 2 + (b + a) / 2;
	}
	return finalCoordinates;
}
double measure(double a, double b, double parts, vector<double> weight, vector<double> coordinates, int current_max_parts, double newR) {
	double value = 0.;
	vector<double> newCoordinates = resizeCoordinates(coordinates, a, b, parts - 1);
	for (int i = 0; i < parts - 1; i++) {
		double func = 2 * sqrt(pow(newR, 2) - pow(newCoordinates[i], 2));
		value += weight[i] * func * (b - a) / 2;
	}
	return value;
}
double measureS(double a, double b, int parts, vector<double> weight, vector<double> coordinates, int current_max_parts, double newR) {
	double S = 0.;
	vector<double> coordinatesX(current_max_parts + 1);
	defineCoordinates(coordinatesX, a, b, current_max_parts);
	for (int i = 0; i < current_max_parts; i++) {
		S += measure(coordinatesX[i], coordinatesX[i + 1], parts, weight, coordinates, current_max_parts, newR);	
	}
	return S;
}
double measureV(double a, double b, int parts, vector<double> weight, vector<double> coordinates, int current_max_parts) {
	double V = 0.;
	vector<double> newCoordinates = resizeCoordinates(coordinates, a, b, parts - 1);
	for (int i = 0; i < newCoordinates.size(); i++) {
		double newR = sqrt(pow(R, 2) - pow(newCoordinates[i], 2));
		double S = measureS(x - newR, x + newR, parts, weight, coordinates, current_max_parts, newR);
		V += weight[i] * S * (b - a) / 2;
	}
	return V;
}
int main() {
	//system("color d3");
	ofstream fout;
	fout.open("V.csv");
	double compare = (4. / 3.) * M_PI * pow(R,3);
	cout << "R = " << R << endl << setprecision(8) << "4/3 * PI * R^3 = " << compare << endl;
	vector <vector<double>> GLcoordinates(3, vector<double>(5));
	GLcoordinates[0][0] = 0.;
	GLcoordinates[1][0] = -sqrt(3. / 5.);
	GLcoordinates[1][1] = 0.;
	GLcoordinates[1][2] = sqrt(3. / 5.);
	GLcoordinates[2][0] = -1. / 3. * sqrt(5. + 2. * sqrt(10. / 7.));
	GLcoordinates[2][1] = -1. / 3. * sqrt(5. - 2. * sqrt(10. / 7.));
	GLcoordinates[2][2] = 0.;
	GLcoordinates[2][3] = 1. / 3. * sqrt(5. - 2. * sqrt(10. / 7.));
	GLcoordinates[2][4] = 1. / 3. * sqrt(5. + 2. * sqrt(10. / 7.));
	vector<vector<double>> weight(3, vector<double>(5));
	weight[0][0] = 2.;
	weight[1][0] = 5. / 9.;
	weight[1][1] = 8. / 9.;
	weight[1][2] = 5. / 9.;
	weight[2][0] = (322. - 13. * sqrt(70.)) / 900.;
	weight[2][1] = (322. + 13. * sqrt(70.)) / 900.;
	weight[2][2] = 128. / 225.;
	weight[2][3] = (322. + 13. * sqrt(70.)) / 900.;
	weight[2][4] = (322. - 13. * sqrt(70.)) / 900.;
	int GLparts[] = { 2, 4, 6 };
	int max_parts = pow(2, 12);
	vector<double> V_GL(3);
	for (int i = 1; i <= max_parts; i *= 2) {
		vector<double> coordinatesZ(i + 1);
		defineCoordinates(coordinatesZ, z - R, z + R, i);
		for (int j = 0; j < i; j++) {
			for (int k = 0; k < 3; k++) {
				V_GL[k] += measureV(coordinatesZ[j], coordinatesZ[j + 1], GLparts[k], weight[k], GLcoordinates[k], i); 
			}
		}
		fout << abs(V_GL[0] - compare) << ";" << abs(V_GL[1] - compare) << ";" << abs(V_GL[2] - compare) << endl;
		cout << abs(V_GL[0] - compare) << "; " << abs(V_GL[1] - compare) << "; " << abs(V_GL[2] - compare) << endl;
		V_GL[0] = 0.;
		V_GL[1] = 0.;
		V_GL[2] = 0.;
	}
	fout.close();
	system("pause");
	return 0;
}