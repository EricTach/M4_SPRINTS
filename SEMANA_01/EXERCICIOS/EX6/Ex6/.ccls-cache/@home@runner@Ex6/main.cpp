#include <iostream>
using namespace std;

int main() {
  int nume = 0, frente = 0, tras = 0, esq = 0, dir = 0;
  
  cout << "Insira a distância da frente: " << endl;
  cin >> frente;
  
  cout << "Insira a distância de trás: " << endl;
  cin >> tras;
  
  cout << "Insira a distância da esquerda: " << endl;
  cin >> esq;

  cout << "Insira a distância da direita: " << endl;
  cin >> dir;

  cout << "A distância que deve ser percorrida por cada uma das direções são: " <<endl;
  cout << "{Trás: " << tras << ", Frente: " << frente << ", Direita: " << dir << ", Esquerda: " << esq << "}";
}