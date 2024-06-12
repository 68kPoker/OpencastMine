#pragma once

#include <ilopl/iloopl.h>
#include <iostream>
#include <fstream>
#include <string>

#define MAX_LEVEL 4

using namespace std;

class OpencastMine {

	typedef IloArray<IloBoolVarArray> IloBoolVar2DArray;
	typedef IloArray<IloBoolVar2DArray> IloBoolVar3DArray;
	typedef IloArray<IloNumArray> IloNum2DArray;
	typedef IloArray<IloNum2DArray> IloNum3DArray;
	IloEnv m_env;
	
	IloBoolVar3DArray m_dig;
	IloNum3DArray m_values;
	IloIntArray m_levelCosts;

	IloModel m_model;
	IloCplex m_algorithm;
	
	IloInt m_maxLevel, m_metalValue;
	IloNumExpr m_expr;
	IloObjective m_max;
	
public:	
	OpencastMine(const int *levelCosts, const int metalValue, const double values[MAX_LEVEL][MAX_LEVEL][MAX_LEVEL]) :
		m_maxLevel(MAX_LEVEL), m_metalValue(metalValue), m_env(), 
		m_model(m_env), m_algorithm(m_model),
		m_levelCosts(m_env, MAX_LEVEL),
		m_values(m_env, MAX_LEVEL),
		m_dig(m_env, MAX_LEVEL),
		m_expr(m_env) {
		int i, j, k;

		for (i = 0; i < m_maxLevel; i++) {
			m_levelCosts[i] = levelCosts[i];

			m_values[i] = IloNum2DArray(m_env, m_maxLevel);
			m_dig[i] = IloBoolVar2DArray(m_env, m_maxLevel);
			for (j = 0; j < m_maxLevel; j++) {
				m_values[i][j] = IloNumArray(m_env, m_maxLevel);
				m_dig[i][j] = IloBoolVarArray(m_env, m_maxLevel);
				for (k = 0; k < m_maxLevel; k++) {
					m_values[i][j][k] = values[i][j][k];							
					ostringstream ss;

					ss << "Dig (" << i << "," << j << "," << k << ")";
					
					m_dig[i][j][k] = IloBoolVar(m_env, ss.str().c_str());

					/* Funkcja celu */

					if (j < m_maxLevel - i && k < m_maxLevel - i) {
						m_expr += m_dig[i][j][k] * (m_values[i][j][k] * m_metalValue / 100.0 - m_levelCosts[i]);
						/* Ograniczenia */

						if (i > 0) {
							
							m_model.add(m_dig[i - 1][j][k] - m_dig[i][j][k] >= 0);
							m_model.add(m_dig[i - 1][j + 1][k] - m_dig[i][j][k] >= 0);
							m_model.add(m_dig[i - 1][j + 1][k + 1] - m_dig[i][j][k] >= 0);
						}
					}

					

					
				}
			}
		}
		m_max = IloMaximize(m_env, m_expr);
		m_model.add(m_max);
		
		m_algorithm.solve();

		ofstream output("Wyniki.txt");
		output << "Kopalnia odkrywkowa" << endl;
		output << "Wartosc funkcji celu: " << m_algorithm.getObjValue() << endl;
		for (i = 0; i < m_maxLevel; i++)
		{
			output << "Poziom " << i + 1 << " (koszt " << m_levelCosts[i] << ")" << endl;
			for (j = 0; j < m_maxLevel - i; j++)
			{
				for (k = 0; k < m_maxLevel - i; k++)
				{
					output << "(" << j << "," << k << ") ";
					output << "Wartosc: " << m_values[i][j][k] * m_metalValue / 100 << " ";
					if (m_algorithm.getValue(m_dig[i][j][k]))
					{
						output << "(Wykopane)";						
					}
					output << endl;
				}
			}
		}
	}
};
