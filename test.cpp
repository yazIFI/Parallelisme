#include <iostream>
using namespace std;
 
int main(int argc, char** argv) {
 
    // Données :
    int values[] = { -1, 4, 4, -1, -2, -4, 11, -1 };
    int maxValues = 8;
 
    // Résultat :
    int startIndex = 0;
    int stopIndex = 0;
    int maxSumValue = values[0];
 
    // Data :
    int *sumValues = new int[maxValues];
 
    // Etape 1 : on stocke la somme des termes dans sumValues de telle sorte que sumValues[i] = sum(values[0], ... values[i])
    int sumValue = 0;
    for ( int iStopIndex = 0 ; iStopIndex < maxValues ; iStopIndex++ ) {
        sumValue += values[iStopIndex];
        sumValues[iStopIndex] = sumValue;
        if ( sumValue > maxSumValue ) {
            stopIndex = iStopIndex;
            maxSumValue = sumValue;
        }
    }
 
    // Etape 2 : retirer progressivement les valeurs de début dans les sommes.
    for( int iStartIndex = 0 ; iStartIndex < (maxValues-1) ; iStartIndex++ ) {
        for ( int iStopIndex = (iStartIndex+1) ; iStopIndex < maxValues ; iStopIndex++ ) {
            sumValues[iStopIndex] -= values[iStartIndex];
            if ( sumValues[iStopIndex] > maxSumValue ) {
                stopIndex = iStopIndex;
                startIndex = iStartIndex+1;
                maxSumValue = sumValues[iStopIndex];
            }
        }
    }
 
    delete[] sumValues;
 
    // Fin :
    cout << "start: " << startIndex << endl;
    cout << "stop: " << stopIndex << endl;
    cout << "sum:" << maxSumValue << endl;
 
    return 0;
 
}