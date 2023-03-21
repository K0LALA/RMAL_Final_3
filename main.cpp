#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// Retourne vrai si n est un carré parfait
bool estCarreParfait(int n, const vector<int> & carres) {
    return find(carres.begin(), carres.end(), n) != carres.end();
}

// Créer une liste de nombres valides pour un nombre et inférieurs au max
vector<int> obtenirNombresOK(int max, int nombre, const vector<int>& carres)
{
    vector<int> nombresOK;

    for (int i(0); i < carres.size(); ++i)
    {
        // Si la différence du carré parfait par rapport au nombre actuel
        // est supérieure au nombre maximum de la suite
        // OU
        // est inférieure ou égale à 0
        // OU
        // est égale à i
        // On passe un prochain carré parfait
        if (carres[i] - nombre > max ||
            carres[i] - nombre <= 0 ||
            carres[i] - nombre == nombre) continue;

        nombresOK.push_back(carres[i] - nombre);
    }

    return nombresOK;
}
 
// Renvoie true si la permutation envoyée est valide
bool estPermutationValide(const vector<int>& permutation, const vector<int> & carres) {
    // On prend la taille de la permutation
    int taille = permutation.size();
    // Pour tous les binômes (d'où le taille - 1 car le dernier ne peut pas être avec le suivant)
    for (int i = 0; i < taille - 1; ++i) {
        // On regarde si la somme des deux est un carré parfait
        if (!estCarreParfait(permutation[i] + permutation[i + 1], carres))
            // Si non on renvoie false
            return false;
    }
    // Si on arrive ici, c'est que tous les binômes on été testés et sont valides car un return signifie qu'on sort de la fonction
    return true;
}

// Cherche une nouvelle permutation pour la suite
bool chercherPermutation(int n, vector<int>& permutation, vector<vector<int>>& nombresOK, const vector<int> & carres) {
    if (permutation.size() == n)
        return estPermutationValide(permutation, carres);

    // On récupère le dernier de la suite
    int last = permutation.back();
    // Pour tous les nombres valides avec le dernier
    for (int i = 0; i < nombresOK[last - 1].size(); ++i) {
        if (nombresOK[last - 1][i] > n)
            break;

        // On récupère le nombre i valide avec le dernier
        int nombre = nombresOK[last - 1][i];
        // Si ce nombre n'est pas déjà dans la suite actuelle
        if (find(permutation.begin(), permutation.end(), nombre) == permutation.end()) {
            // On l'ajoute à la suite
            permutation.push_back(nombre);
            // On cherche une nouvelle permutation en renvoyant les mêmes paramètres que la fonction à reçu, juste avec la permutation changée
            if (chercherPermutation(n, permutation, nombresOK, carres))
                // Si une permutation a été trouvée, on renvoie true
                return true;
            // On enlève le dernier élément de la permtation car cela signifie qu'on a pas pu finir la permutation avec le chox d'avant
            permutation.pop_back();
        }
    }
    // Renvoie false si aucune permutation n'a été trouvée
    // Comme vu au-dessus, si on renvoie false, on revient en arrière dans la suite
    return false;
}

int main() {
    cout << "Ce programme genere des suites de nombres ou la somme de deux nombres consecutifs forme un carre parfait" << endl;
    cout << "Pour l'utiliser, il suffit de choisir une plage de nombres pour lesquels des suites vont etre generees, le minimum et le maximum inclus" << endl;
    cout << "Le minimum doit etre superieur ou egal a 2 et la maximum ne doit pas etre plus petit que le minimum mais il peut etre egal" << endl;

    // Minimum
    int min = 0;
    do {
        cout << "min = ";
        cin >> min;
    } while (min < 2);
    
    // Maximum
    int max = 0;
    do {
        cout << "max = ";
        cin >> max;
    } while (max < min);

    // On définit les carrés parfaits jusqu'au plus haut possible (somme des deux maximum)
    vector<int> carresParfaits;
    for (int j(1); j <= sqrt(max + max - 1); ++j)
        carresParfaits.push_back(pow(j, 2));

    // Pour avoir les nombres valides de 1, il faut choisir l'index 0
    vector<vector<int>> nombresOK;
    // On ajoute les vecteurs que retourne la fonction obtenirNombresOK au vecteur 2D qui les contient tous
    for (int j(1); j < max + 1; ++j)
        nombresOK.push_back(obtenirNombresOK(max, j, carresParfaits));

    // Pour tous les nombres dans la plage
    for (int i(min); i < max + 1; ++i)
    {
        // On test avec chaque nombre comme départ
        for (int j(1); j < i + 1; ++j)
        {
            // On créer notre suite (vide pour l'instant)
            vector<int> suite = { j };
            // Si la fonction chercherPermutation a réussi à trouver une permutation valide (elle renvoie true)
            if (chercherPermutation(i, suite, nombresOK, carresParfaits)) {
                // On affiche la permutation
                cout << "Une permutation valide pour " << i << " est : ";
                for (int k(0); k < suite.size(); ++k)
                    cout << suite[k] << "-";
                cout << endl;
            }
        }
    }    

    return 0;
}
