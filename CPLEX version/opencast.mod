/*********************************************
 * OPL 22.1.1.0 Opencast Mining Model
 * Author: Kaminski P., Szacki R., Sosnowski M.
 * Creation Date: 9 maj 2024 at 10:20:00
 *********************************************/
range level = 1..4;
int max_level = 4;
dvar int+ W[level] [level] [level] in 0..1;
float V[level][level][level] = ...;
int level_cost[level] = ...;
int metal_value = ...;
 
 
maximize 
	sum (m in 1..max_level, n in 1..max_level-m+1, o in 1..max_level-m+1)
	  (W[m][n][o] * (V[m][n][o] * metal_value / 100 - level_cost[m]));
subject to
{
	forall (m in 2..max_level, n in 1..max_level-m+1, o in 1..max_level-m+1) 
	{
		W[m-1][n][o] - W[m][n][o] >= 0;
		W[m-1][n+1][o] - W[m][n][o] >= 0;
		W[m-1][n][o+1] - W[m][n][o] >= 0;
		W[m-1][n+1][o+1] - W[m][n][o] >= 0;
	}		
}
