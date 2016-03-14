/**
 * @file main.cpp
 * @brief Programme principal
 * @author Damien Morel et Maxime Mikotajewski
 */
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Ensemble.hpp"
#include "Point.hpp"

#include "Front.hpp"
#include "Traitement.hpp"
#include "Graham.hpp"
#include "LoaderPoint.hpp"
#include "SquareGenerator.hpp"
#include "ParetoDisplay.hpp"
#include "EnsembleDisplay.hpp"

#include "Exporter.hpp"

using namespace std;


int main(int, char**){
    //string filename  = "data.txt";
    LoaderPoint loader;
    // Remplit un ensemble de points en static (Il n'y a dans tous les cas qu'un seul ensemble de point par exécution du programme)
    //loader.loadFile(filename);


    SquareGenerator generator(12);
    generator.generateSquare(-2,-2,2,40);
    generator.generateSquare(4,4,3,60);

    // Graham hérite de Traitement.
    Traitement *t = new Graham();

    EnsembleDisplay dis(1600,900) ;

    Front f(t);

    std::srand(std::time(0));

    f.globalHull();

    //cerr << f.getCurrent();

    /*
    for(int i = 0; i < 10; ++i)
    f.removePoint();
*/
    //cerr << "\n\n";

    //cerr << f.getCurrent();
   f.constructionFirstPareto();
    cerr << "Pareto size : " << f.getParetoSize() << "\n";
    //f.localSearch_v2(10);


    //f.showFront();
    //f.addPoint();
    //f.removePoint();
/*
    dis.setCurrentSet(f.getCurrent());
    dis.drawPoints();
    dis.drawConvexHull();
*/
/*

    ParetoDisplay p(f.getParetoSize(), 1600,900);

    vector<Point> v = f.getParetoPoints();

    for(Point point : v){
        p.addPoint(&point);
    }
*/
    Exporter exp;
    exp.exportData(f);

 //   p.drawParetoFront();


    delete t;
    Ensemble::destroy();
    return 0;
}


/*
    // Génération de points sur un carré (peut facilement générer sur deux carrés avec deux generateSquare)
int main(int, char**){
    SquareGenerator generator(12);
    generator.generateSquare(-2,-2,2,40);
    generator.generateSquare(4,4,3,60);


    for(std::vector<Point*>::iterator it = Ensemble::points.begin();
        it!=Ensemble::points.end();
        ++it){
        cout << *(*it) << endl;
    }
}
*/
