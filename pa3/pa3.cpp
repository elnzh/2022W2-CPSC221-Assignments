// File:        pa3.cpp
// Author:      cs221 instructors
// Date:        2021-03-03
// Description: Partial test of PA3 functionality
//              Reads Point data from external files
//              Produces PNG images of the point sets

#include "sqtree.h"
#include "stats.h"
int main() {

  // read in image
  PNG orig;
  //orig.readFromFile("images/orig/small1.png");
  //orig.readFromFile("images/orig/small2.png");
  //orig.readFromFile("images/orig/pacman.png");
  //orig.readFromFile("images/orig/huckleberry_hound.png");
  //orig.readFromFile("images/orig/rocky.png");
  //orig.readFromFile("images/orig/rocky_bullwinkle.png");
  orig.readFromFile("images/orig/colour.png");
  //orig.readFromFile("images/orig/klee-flora-on-sand.png");
  //orig.readFromFile("images/orig/stanley-totem-poles.png");




 // stats *s=new stats(orig);
//    std::cout<<"r: "<<endl;
//  for(unsigned int i=0;i<orig.width();i++){
//      for(unsigned int j=0;j<orig.height();j++){
//          std::cout<<(unsigned int)orig.getPixel(i,j)->r;
//          std::cout<<" ";
//      }
//      std::cout<<std::endl;
//  }
//    pair<int,int>temp;
//    temp.first=0;
//    temp.second=0;
//
//    std::cout<<s->getVar(temp, 2, 2) <<endl;;


//    std::cout<<"check r_sum: "<<endl;
//    for(unsigned int i=0;i<orig.width();i++){
//        for(unsigned int j=0;j<orig.height();j++){
//            std::cout<<s->sumRed[i][j];
//            std::cout<<" ";
//        }
//        std::cout<<std::endl;
//    }

//    std::cout<<"check r_sumsq: "<<endl;
//    for(unsigned int i=0;i<orig.width();i++){
//        for(unsigned int j=0;j<orig.height();j++){
//            std::cout<<s->sumsqRed[i][j];
//            std::cout<<" ";
//        }
//        std::cout<<std::endl;
//    }

//    std::cout<<"check var: "<<endl;
//    pair<int,int> temp;
//    temp.first=0;
//    temp.second=0;
//    std::cout<<"check var: whole "<<endl;
//    std::cout<<s->getVar(temp,8,8)<<endl;
//    std::cout<<"check var: half "<<endl;
//    std::cout<<s->getVar(temp,4,4)<<endl;
//    std::cout<<"check var: less than half "<<endl;
//    std::cout<<s->getVar(temp,3,3)<<endl;
//    std::cout<<"check var: more than half "<<endl;
//    std::cout<<s->getVar(temp,5,5)<<endl;






    //std::cout<<"main: 79"<<endl;

  // use it to build a sqtree (try other tolerances)
  SQtree t(orig,100000.0);

//  // copy the tree (to show you can)
  SQtree tCopy(t);
//
//  // render the sqtree
  PNG pic = t.render();
//
//  // write it out
    //std::cout<<"size of nodes:"<<t.size()<<endl;
    pic.writeToFile("images/out/small1.png");
    //pic.writeToFile("images/out/small2.png");

  return 0;
}
