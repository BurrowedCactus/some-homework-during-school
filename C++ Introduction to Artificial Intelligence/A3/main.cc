#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

int main(){
	ifstream myfile ("trainData.txt");
	int Sloepnea_t = 0;
	int Foriennditis_t = 0;
	int Degar_spots_t = 0;
	int normal = 0;
	int TRIMONO_HT_S_t = 0;
	int DS_none = 0;
	int DS_mild = 0;
	int DS_severe = 0;
/*
	array Symptoms_t saves following data: 

	Sloepnea		normal			N/A
	Foriennditis		TRIMONO-HT/S		none
	Degar_spots					mild
							severe
*/
	int Symptoms_t[3][2][4] = {0};
	int count[2][4] = {0};

	int** array = new int[2000][5];
	if (myfile.is_open()){
		string line;
		int i = 0;
		while (getline(myfile, line)){
			int Sloepnea, Foriennditis, Degar_spots, TRIMONO_HT_S, Dunetts_Syndrome;
			istringsteam iss(line);
			iss >> Sloepnea >> Foriennditis >> Degar_spots >> TRIMONO_HT_S >> Dunetts_Syndrome;
			array[i] = {Sloepnea , Foriennditis , Degar_spots , TRIMONO_HT_S , Dunetts_Syndrome + 1};
			++i;
			if (Sloepnea == 1){
				++Symptoms_t[0][TRIMONO_HT_S][Dunetts_Syndrome + 1];
			}
			if (Foriennditis == 1){
				++Symptoms_t[1][TRIMONO_HT_S][Dunetts_Syndrome + 1];
			}
			if (Degar_spots == 1){
				++Symptoms_t[2][TRIMONO_HT_S][Dunetts_Syndrome + 1];
			}
			++count[TRIMONO_HT_S][Dunetts_Syndrome + 1];
			switch(TRIMONO_HT_S){
				case 0:
					++normal;
					break;
				case 1:
					++TRIMONO_HT_S_t;
					break;
				default:
					break;
			}
			switch(Dunetts_Syndrome){
				case 0:
					++DS_none;
					break;
				case 1:
					++DS_mild;
					break;
				case 2:
					++DS_severe;
					break;
				case -1:
				default:
					break;
			}
			
		}
		myfile.close();
	} else {
		cerr << "Unable to open trainData.txt" << endl;
	}
	double Gene_normal = 0.9
	double Gene_special = 0.1
	double Form_none = 0.5;
	double Form_mild = 0.25;
	double Form_severe = 0.25;

	double Symptoms_conditional[18] = { 1.0 * Symptoms_t[0][0][1] / count[0][1], 1.0 * Symptoms_t[0][1][1] / count[1][3],
	                                    1.0 * Symptoms_t[1][0][1] / count[0][1], 1.0 * Symptoms_t[1][1][1] / count[1][3],
	                                    1.0 * Symptoms_t[2][0][1] / count[0][1], 1.0 * Symptoms_t[2][1][1] / count[1][3],
	                                    1.0 * Symptoms_t[0][0][2] / count[0][2], 1.0 * Symptoms_t[0][1][2] / count[1][3],
	                                    1.0 * Symptoms_t[1][0][2] / count[0][2], 1.0 * Symptoms_t[1][1][2] / count[1][3],
	                                    1.0 * Symptoms_t[2][0][2] / count[0][2], 1.0 * Symptoms_t[2][1][2] / count[1][3],
	                                    1.0 * Symptoms_t[0][0][3] / count[0][3], 1.0 * Symptoms_t[0][1][3] / count[1][3],
	                                    1.0 * Symptoms_t[1][0][3] / count[0][3], 1.0 * Symptoms_t[1][1][3] / count[1][3],
	                                    1.0 * Symptoms_t[2][0][3] / count[0][3], 1.0 * Symptoms_t[2][1][3] / count[1][3] };
	double to_exit = 0;
	double to_exit_last = -100;


	while (true){
		double Symptoms[18] = {  Symptoms_conditional[0] * Form_none * Gene_normal,  Symptoms_conditional[1] * Form_none * Gene_special,
		                         Symptoms_conditional[2] * Form_none * Gene_normal,  Symptoms_conditional[3] * Form_none * Gene_special,
		                         Symptoms_conditional[4] * Form_none * Gene_normal,  Symptoms_conditional[5] * Form_none * Gene_special,
		                         Symptoms_conditional[6] * Form_mild * Gene_normal,  Symptoms_conditional[7] * Form_mild * Gene_special,
		                         Symptoms_conditional[8] * Form_mild * Gene_normal,  Symptoms_conditional[9] * Form_mild * Gene_special,
		                         Symptoms_conditional[10] * Form_mild * Gene_normal,  Symptoms_conditional[11] * Form_mild * Gene_special,
		                         Symptoms_conditional[12] * Form_severe * Gene_normal,  Symptoms_conditional[13] * Form_severe * Gene_special,
		                         Symptoms_conditional[14] * Form_severe * Gene_normal,  Symptoms_conditional[15] * Form_severe * Gene_special,
		                         Symptoms_conditional[16] * Form_severe * Gene_normal,  Symptoms_conditional[17] * Form_severe * Gene_special };

	
		double Gene[18] = { Symptoms[0] / (Symptoms[0] + Symptoms[1]), Symptoms[1] / (Symptoms[0] + Symptoms[1]),
		                    Symptoms[2] / (Symptoms[2] + Symptoms[3]), Symptoms[3] / (Symptoms[2] + Symptoms[3]),
		                    Symptoms[4] / (Symptoms[4] + Symptoms[5]), Symptoms[5] / (Symptoms[4] + Symptoms[5]),
		                    Symptoms[6] / (Symptoms[6] + Symptoms[7]), Symptoms[7] / (Symptoms[6] + Symptoms[7]),
		                    Symptoms[8] / (Symptoms[8] + Symptoms[9]), Symptoms[9] / (Symptoms[8] + Symptoms[9]),
		                    Symptoms[10] / (Symptoms[10] + Symptoms[11]), Symptoms[11] / (Symptoms[10] + Symptoms[11]),
	 	                    Symptoms[12] / (Symptoms[12] + Symptoms[13]), Symptoms[13] / (Symptoms[12] + Symptoms[13]),
		                    Symptoms[14] / (Symptoms[14] + Symptoms[15]), Symptoms[15] / (Symptoms[14] + Symptoms[15]),
	 	                    Symptoms[16] / (Symptoms[16] + Symptoms[17]), Symptoms[17] / (Symptoms[16] + Symptoms[17]) };

		double Form[18] = { Symptoms[0] / (Symptoms[0] + Symptoms[6] + Symptoms[12]), Symptoms[1] / (Symptoms[1] + Symptoms[7] + Symptoms[13]),
	        	            Symptoms[2] / (Symptoms[2] + Symptoms[8] + Symptoms[14]), Symptoms[3] / (Symptoms[3] + Symptoms[9] + Symptoms[15]),
		                    Symptoms[4] / (Symptoms[4] + Symptoms[10] + Symptoms[16]), Symptoms[5] / (Symptoms[5] + Symptoms[11] + Symptoms[17]),
		                    Symptoms[6] / (Symptoms[0] + Symptoms[6] + Symptoms[12]), Symptoms[7] / (Symptoms[1] + Symptoms[7] + Symptoms[13]),
		                    Symptoms[8] / (Symptoms[2] + Symptoms[8] + Symptoms[14]), Symptoms[9] / (Symptoms[3] + Symptoms[9] + Symptoms[15]),
		                    Symptoms[10] / (Symptoms[4] + Symptoms[10] + Symptoms[16]), Symptoms[11] / (Symptoms[5] + Symptoms[11] + Symptoms[17]),
		                    Symptoms[12] / (Symptoms[0] + Symptoms[6] + Symptoms[12]), Symptoms[13] / (Symptoms[1] + Symptoms[7] + Symptoms[13]),
		                    Symptoms[14] / (Symptoms[2] + Symptoms[8] + Symptoms[14]), Symptoms[15] / (Symptoms[3] + Symptoms[9] + Symptoms[15]),
		                    Symptoms[16] / (Symptoms[4] + Symptoms[10] + Symptoms[16]), Symptoms[17] / (Symptoms[5] + Symptoms[11] + Symptoms[17]) };

		double count2[18][2] = {0};

		//saved in array[2000][5] :  Sloepnea , Foriennditis , Degar_spots , TRIMONO_HT_S , Dunetts_Syndrome + 1;
		for (int i = 0; i < 2000; ++i){
			if        (array[i][4] == 1 && array[i][3] == 0 && array[i][0] == 1){
				to_exit += Symptoms[0];
				count2[0][0] += Gene[0];
				count2[0][1] += Form[0];
			} else if (array[i][4] == 1 && array[i][3] == 1 && array[i][0] == 1){
				to_exit += Symptoms[1];
				count2[1][0] += Gene[1];
				count2[1][1] += Form[1];
			} else if (array[i][4] == 1 && array[i][3] == 0 && array[i][0] == 2){
				to_exit += Symptoms[2];
				count2[2][0] += Gene[2];
				count2[2][1] += Form[2];
			} else if (array[i][4] == 1 && array[i][3] == 1 && array[i][0] == 2){
				to_exit += Symptoms[3];
				count2[3][0] += Gene[3];
				count2[3][1] += Form[3];
			} else if (array[i][4] == 1 && array[i][3] == 0 && array[i][0] == 3){
				to_exit += Symptoms[4];
				count2[4][0] += Gene[4];
				count2[4][1] += Form[4];
			} else if (array[i][4] == 1 && array[i][3] == 1 && array[i][0] == 3){
				to_exit += Symptoms[5];
				count2[5][0] += Gene[5];
				count2[5][1] += Form[5];
			} else if (array[i][4] == 2 && array[i][3] == 0 && array[i][0] == 1){
				to_exit += Symptoms[6];
				count2[6][0] += Gene[6];
				count2[6][1] += Form[6];
			} else if (array[i][4] == 2 && array[i][3] == 1 && array[i][0] == 1){
				to_exit += Symptoms[7];
				count2[7][0] += Gene[7];
				count2[7][1] += Form[7];
			} else if (array[i][4] == 2 && array[i][3] == 0 && array[i][0] == 2){
				to_exit += Symptoms[8];
				count2[8][0] += Gene[8];
				count2[8][1] += Form[8];
			} else if (array[i][4] == 2 && array[i][3] == 1 && array[i][0] == 2){
				to_exit += Symptoms[9];
				count2[9][0] += Gene[9];
				count2[9][1] += Form[9];
			} else if (array[i][4] == 2 && array[i][3] == 0 && array[i][0] == 3){
				to_exit += Symptoms[10];
				count2[10][0] += Gene[10];
				count2[10][1] += Form[10];
			} else if (array[i][4] == 2 && array[i][3] == 1 && array[i][0] == 3){
				to_exit += Symptoms[11];
				count2[11][0] += Gene[11];
				count2[11][1] += Form[11];
			} else if (array[i][4] == 3 && array[i][3] == 0 && array[i][0] == 1){
				to_exit += Symptoms[12];
				count2[12][0] += Gene[12];
				count2[12][1] += Form[12];
			} else if (array[i][4] == 3 && array[i][3] == 1 && array[i][0] == 1){
				to_exit += Symptoms[13];
				count2[13][0] += Gene[13];
				count2[13][1] += Form[13];
			} else if (array[i][4] == 3 && array[i][3] == 0 && array[i][0] == 2){
				to_exit += Symptoms[14];
				count2[14][0] += Gene[14];
				count2[14][1] += Form[14];
			} else if (array[i][4] == 3 && array[i][3] == 1 && array[i][0] == 2){
				to_exit += Symptoms[15];
				count2[15][0] += Gene[15];
				count2[15][1] += Form[15];
			} else if (array[i][4] == 3 && array[i][3] == 0 && array[i][0] == 3){
				to_exit += Symptoms[16];
				count2[16][0] += Gene[16];
				count2[16][1] += Form[16];
			} else if (array[i][4] == 3 && array[i][3] == 1 && array[i][0] == 3){
				to_exit += Symptoms[17];
				count2[17][0] += Gene[17];
				count2[17][1] += Form[17];
			}
		}

		if (abs(to_exit - to_exit_last) <= 0.01) {
			break;
		}

		to_exit_last = to_exit;
		to_exit = 0;

		sum_gene = 0;
		sum_form = 0;
		for (int i = 0; i < 18; ++i){
			sum_gene += count2[i][0];
			sum_form += count2[i][1];
		}	

		Gene_normal = (count2[0][0] + count2[2][0] + count2[4][0] + count2[6][0] + count2[8][0] + count2[10][0] +
		               count2[12][0] + count2[14][0] + count2[16][0]) / sum_gene;
		Gene_special = 1 - Gene_normal;
		Form_none = (count2[0][1] + count2[1][1] + count2[6][1] + count2[7][1] + count2[12][1] + count2[13][1]) / sum_form;
		Form_mild = (count2[3][1] + count2[4][1] + count2[8][1] + count2[9][1] + count2[14][1] + count2[15][1]) / sum_form;
		Form_severe = 1 - Form_none - Form_mild;


/*
		dont know how to update Symptoms_conditional[18] given Gene[18], Form[18] 
	
		Symptoms_conditional[0] =  ;
		Symptoms_conditional[1] = 
		...
*/

	}

	delete[] array;
}