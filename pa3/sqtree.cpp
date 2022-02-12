/**
 *
 * shifty quadtree (pa3)
 * sqtree.cpp
 * This file will be used for grading.
 *
 */

#include "sqtree.h"

// First Node constructor, given.
SQtree::Node::Node(pair<int,int> ul, int w, int h, RGBAPixel a, double v)
  :upLeft(ul),width(w),height(h),avg(a),var(v),NW(NULL),NE(NULL),SE(NULL),SW(NULL)
{}

// Second Node constructor, given
SQtree::Node::Node(stats & s, pair<int,int> ul, int w, int h)
  :upLeft(ul),width(w),height(h),NW(NULL),NE(NULL),SE(NULL),SW(NULL) {
  avg = s.getAvg(ul,w,h);
  var = s.getVar(ul,w,h);
}

// SQtree destructor, given.
SQtree::~SQtree() {
  clear();
}

// SQtree copy constructor, given.
SQtree::SQtree(const SQtree & other) {
  copy(other);
}

// SQtree assignment operator, given.
SQtree & SQtree::operator=(const SQtree & rhs) {
  if (this != &rhs) {
    clear();
    copy(rhs);
  }
  return *this;
}

/**
 * SQtree constructor given tolerance for variance.
 * * * The constructor first builds the stats object used to compute
   * the variability and average of image subrectangles so that it can
   * pick the best partition of a Node of size w x h in O(wh) time.
   * Then it recursively partitions Nodes, starting at the root and
   * always using the best partition, until the Node's variability is
   * at most tol or the Node is a single pixel.
   * Default tolerance is 0.0.
 *
 */
SQtree::SQtree(PNG & imIn, double tol) {
    stats s(imIn);
    pair<int,int> origin;
    //img=new PNG(imIn);
    img=&imIn;
    origin.first=0;
    origin.second=0;
    //std::cout<<"sqtree59"<<endl;
    root=buildTree( s, origin, img->width(), img->height(), tol);
    //std::cout<<"sqtree61"<<endl;
//    if(root->SE== nullptr) std::cout<<"SE taken"<<endl;
//    if(root->SW== nullptr) std::cout<<"SW taken"<<endl;
//    if(root->NE== nullptr) std::cout<<"NE taken"<<endl;
//    if(root->NW== nullptr) std::cout<<"NW taken"<<endl;

}

/**
 * Helper for the SQtree constructor.

 */
SQtree::Node * SQtree::buildTree(stats & s, pair<int,int> & ul, int w, int h, double tol) {
    double v1;
    double v2;
    double v3;
    double v4;
    double max=0;
    double min=INT_MAX;
    pair<int,int> temp;
    pair<int,int> position_best;

    Node *n=new Node(ul,w,h,s.getAvg(ul,w,h),s.getVar(ul,w,h));
    if(w==1 & h==1 ||s.getVar(ul,w,h)<=tol){
        return n;
    }
    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++) {
           // std::cout<<i<<" "<<j<<endl;
            if(i==0 && j==0 ){
                //std::cout<<"hi 90"<<endl;
            }else{
                if(i==0){
                    v1 = s.getVar(ul,w,j);
                    temp.first = ul.first;
                    temp.second = ul.second+j;
                    v2 = s.getVar(temp, w, h-j);
                    if(v1>=v2){
                        max=v1;
                    }else {
                        max=v2;
                    }
                }else if(j==0){
                    v1 = s.getVar(ul, i, h);
                    temp.first=ul.first+i;
                    temp.second=ul.second;
                    v2=s.getVar(temp, w-i, h);
                    if(v1>=v2){
                        max=v1;
                    }else {
                        max=v2;
                    }
                }else{
                    v1 = s.getVar(ul, i, j);
                    max=v1;
                    temp.first = ul.first + i;
                    temp.second = ul.second;
                    v2 = s.getVar(temp, w - i, j);
                    temp.first = ul.first;
                    temp.second = ul.second + j;
                    v3 = s.getVar(temp, i, h - j);
                    temp.first = ul.first + i;
                    temp.second = ul.second + j;
                    v4 = s.getVar(temp, w - i, h - j);
                    if (v2 >= max) {
                        max = v2;
                    }
                    if (v3 >= max) {
                        max = v3;
                    }
                    if (v4 >= max) {
                        max = v4;
                    }
                }
                //std::cout<<" max===="<<max<<" min===="<<min<<endl;
                if(max<min){
                    min=max;
                    //std::cout<<"hello 131"<<endl;
                    position_best.first = i;
                    position_best.second = j;
                }
            }
        }
    }
//    std::cout<<"hello 153"<<endl;
//    std::cout<<ul.first<<", "<<ul.second<<endl;
//    std::cout<<position_best.first<<" "<<position_best.second<<endl;



        // if (min <= tol) {
        //     //stop split
        //     if(position_best.first == 0){
        //         //std::cout<<position_best.second<<endl;
        //         n->NW=new Node(s,ul,w, position_best.second);
        //         //n->NW=new Node(ul,w,position_best.second,s.getAvg(ul,w,position_best.second),s.getVar(ul,w,position_best.second));
        //         temp.first=ul.first;
        //         temp.second=ul.second+position_best.second;
        //         n->SW=new Node(s,temp,w,h-position_best.second);
        //        // n->SW=new Node(temp,w,h-position_best.second,s.getAvg(temp,w,h-position_best.second),s.getVar(temp,w,h-position_best.second));
        //         return n;
        //     }else if(position_best.second == 0) {
        //         n->NW=new Node(s,ul,position_best.first, h);
        //         //n->NW = new Node(ul, position_best.first, h, s.getAvg(ul, position_best.first, h),
        //                          //s.getVar(ul, position_best.first, h));
        //         temp.first = ul.first + position_best.first;
        //         temp.second = ul.second;
        //         n->NE = new Node(s,temp,w - position_best.first, h);
        //         //n->NE = new Node(temp, w - position_best.first, h, s.getAvg(temp, w - position_best.first, h),
        //                          //s.getVar(temp, w - position_best.first, h));
        //         return n;
        //     } else {
        //         n->NW = new Node(s, ul, position_best.first, position_best.second);
        //         //n->NW = new Node(ul, position_best.first, position_best.second,s.getAvg(ul, position_best.first, position_best.second),s.getVar(ul, position_best.first, position_best.second));
        //         temp.first = ul.first + position_best.first;
        //         temp.second = ul.second;
        //         n->NE = new Node(s, temp, w - position_best.first, position_best.second);
        //         //n->NE = new Node(temp, w - position_best.first, position_best.second,s.getAvg(temp, w - position_best.first, position_best.second),s.getVar(temp, w - position_best.first, position_best.second));
        //         temp.first = ul.first + position_best.first;
        //         temp.second = ul.second + position_best.second;
        //         n->SE = new Node(s, temp, w - position_best.first, h - position_best.second);
        //         //n->SE = new Node(temp, w - position_best.first, h - position_best.second, s.getAvg(temp, w - position_best.first, h - position_best.second),s.getVar(temp, w - position_best.first, h - position_best.second));
        //         temp.first = ul.first;
        //         temp.second = ul.second + position_best.second;
        //         n->SW = new Node(s, temp, position_best.first, h - position_best.second);
        //         //n->SW = new Node(temp, position_best.first, h - position_best.second, s.getAvg(temp, position_best.first, h - position_best.second),s.getVar(temp, position_best.first, h - position_best.second));
        //         return n;
        //     }
        // }else{
            if(position_best.first == 0) {
                n->NW = buildTree(s, ul, w, position_best.second, tol);
                temp.first = ul.first;
                temp.second = ul.second + position_best.second;
                n->SW = buildTree(s, temp, w, h - position_best.second, tol);

            }else if(position_best.second == 0){
                n->NW=buildTree(s,ul,position_best.first,h,tol);
                temp.first=ul.first+position_best.first;
                temp.second=ul.second;
                n->NE = buildTree(s, temp, w - position_best.first, h, tol);
            }else {
                n->NW = buildTree(s, ul, position_best.first, position_best.second, tol);
                temp.first = ul.first+position_best.first;
                temp.second = ul.second;
                n->NE = buildTree(s, temp, w - position_best.first, position_best.second, tol);
                temp.first= ul.first+position_best.first;
                temp.second= ul.second+position_best.second;
                n->SE = buildTree(s, temp, w - position_best.first, h - position_best.second, tol);
                temp.first = ul.first;
                temp.second = ul.second+position_best.second;
                n->SW = buildTree(s, temp, position_best.first, h - position_best.second, tol);
            }
   // }

    return n;


}
  
/**
 * Render SQtree and return the resulting image.
 *
   * Render returns a PNG image consisting of rectangles defined
   * by the leaves in the sqtree.  Draws every leaf node's rectangle
   * onto a PNG canvas using the average color stored in the node.
 */

PNG SQtree::render() {
  // Your code here.

    renderRecursive(root);
    return *img;

}

void SQtree::renderRecursive(Node* n){
    //std::cout<<"hi 250"<<endl;
    if(n != NULL) {
        for (unsigned int i = 0; i < (unsigned)n->width; i++) {
            for (unsigned int j = 0; j < (unsigned)n->height; j++) {
                    img->getPixel(n->upLeft.first + i, n->upLeft.second + j)->r = n->avg.r;
                    img->getPixel(n->upLeft.first + i, n->upLeft.second + j)->g = n->avg.g;
                    img->getPixel(n->upLeft.first + i, n->upLeft.second + j)->b = n->avg.b;
                   // std::cout<<"(w,h)"<<n->upLeft.first + i<<"  "<<n->upLeft.second + j<<endl;
                   if(n->upLeft.first + i>=img->width()){
                       std::cout<<"check 250, error"<<endl;
                   }
                   if(n->upLeft.second + j>=img->height()){
                       std::cout<<"check 250, error"<<endl;
                   }
            }
        }
        renderRecursive(n->NE);
        renderRecursive(n->NW);
        renderRecursive(n->SE);
        renderRecursive(n->SW);
    }
}

/**
 * Delete allocated memory.
 *
   * Destroys all dynamically allocated memory associated with the
   * current SQtree class.
   * You may want a recursive helper function for this one.
 */
void SQtree::clear() {
    clearRecursive(root);
    //img->~PNG();

}

void SQtree::clearRecursive(Node* n){
    if(n==NULL){
        return;
    }

    clearRecursive(n->SE);
    clearRecursive(n->SW);
    clearRecursive(n->NE);
    clearRecursive(n->NW);
    delete n;
    n=NULL;
    return;
}


/**
   * Copies the parameter other SQtree into the current SQtree.
   * Does not free any memory. Called by copy constructor and op=.
   * You may want a recursive helper function for this one.
   * @param other The SQtree to be copied.
   */
void SQtree::copy(const SQtree & other) {
  
    //this->img=new PNG(other.img);
     this->img=other.img;
  
  
    root = copyRecursive(root,other.root);
    
   

}

SQtree::Node * SQtree::copyRecursive(Node* n,Node* other){
    if(other==NULL){
        return NULL;
    }else{
        n=new Node(other->upLeft, other->width, other->height,other->avg,other->var);
        n->SW=copyRecursive(n->SW,other->SW);
        n->SE=copyRecursive(n->SE,other->SE);
        n->NE=copyRecursive(n->NE,other->NE);
        n->NW=copyRecursive(n->NW,other->NW);
        return n;
    }
   
}




/**
   * Return the number of nodes in the tree.
   * You may want a private helper for this.
   */
int SQtree::size() {
    return sizeRecursive(root);
}


int SQtree::sizeRecursive(Node* n){
    if(!n)return 0;
    else return 1+sizeRecursive(n->NE)+sizeRecursive(n->NW)+sizeRecursive(n->SE)+sizeRecursive(n->SW);
}

