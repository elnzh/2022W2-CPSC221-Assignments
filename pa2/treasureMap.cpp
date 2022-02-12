#include "treasureMap.h"
#include "queue.h"
using namespace std;

treasureMap::treasureMap(const PNG & baseim, const PNG & mazeim, pair<int,int> s)
{
    base=baseim;
    maze=mazeim;
    start=s;
//    length.resize(base.width());
//    for(int i=0;i<length.size();i++){
//        length[i].resize(base.height());
//    }
//
    visits.resize(base.width());
    for(int i=0;i<visits.size();i++){
        visits[i].resize(base.height());
        for(int j=0;j<visits[i].size();j++){
            visits[i][j]=false;
        }

    }
}

void treasureMap::setGrey(PNG & im, pair<int,int> loc){
    // changes the pixel at position loc to consist of colour channel
    // values which are 50% of their original. Note that because of
    // our encoding scheme which essentially invalidates the lower
    // order bits, you should compute each value as 2*(x/4), where
    // x is the integer value of a colour channel.

    im.getPixel(loc.first,loc.second)->r=base.getPixel(loc.first,loc.second)->r/2;
    im.getPixel(loc.first,loc.second)->g=base.getPixel(loc.first,loc.second)->g/2;
    im.getPixel(loc.first,loc.second)->b=base.getPixel(loc.first,loc.second)->b/2;


}

void treasureMap::setLOB(PNG & im, pair<int,int> loc, int d){
    //the two most significant
    // bits of d%64 will be used to set the value of the red channel by
    // changing r. The two least significant bits of d%64 will be used
    // to set the value of the blue channel by changing b. And the remaining
    // two bits of d%64 will be used to set the value of the green channel
    // by changing g.
    //
    // Now consider the value of any colour channel, x, represented as an
    // 8 bit binary number. To encode d, simply replace the 2 lower order
    // bits in x with the corresponding bits from d, as described above.

    unsigned char six_bits=d%64;
    unsigned char r_bits=six_bits >>4 & 0b00000011;
    unsigned char g_bits=six_bits >>2 & 0b00000011;
    unsigned char b_bits=six_bits & 0b00000011;
//    std::cout<<"distance: r g b"<<endl;
//    std::cout<<(int)six_bits<<endl;
//    std::cout<<(int)r_bits<<endl;
//    std::cout<<(int)g_bits<<endl;
//    std::cout<<(int)b_bits<<endl;
//    std::cout<<"r before+after:"<<endl;
//    std::cout<<(int)im.getPixel(loc.first,loc.second)->r<<endl;
//    std::cout<<(int)((im.getPixel(loc.first,loc.second)->r & 0b11111100)|r_bits)<<endl;

    im.getPixel(loc.first,loc.second)->r = (im.getPixel(loc.first,loc.second)->r & 0b11111100)|r_bits;
    im.getPixel(loc.first,loc.second)->g = (im.getPixel(loc.first,loc.second)->g & 0b11111100)|g_bits;
    im.getPixel(loc.first,loc.second)->b = (im.getPixel(loc.first,loc.second)->b & 0b11111100)|b_bits;



}

PNG treasureMap::renderMap(){

    PNG *base_copy=new PNG(base);

    //initialize two 2d vectors
    //vector<vector<bool>> visit;
    //vector<vector<bool>> visit( base_copy->width(), vector<bool>( base_copy->height(), false ) );

    vector<vector<bool>> visit;
    visit.resize(base_copy->width());
    for(int i=0;i<visit.size();i++){
        visit[i].resize(base_copy->height());
        for(int j=0;j<visit[i].size();j++){
            visit[i][j]=false;
        }

    }

    vector<vector<int>> length_of_path;
    length_of_path.resize(base_copy->width());
    for(int i=0;i<length_of_path.size();i++){
        length_of_path[i].resize(base_copy->height());
    }

    //initialize the queue
    Queue<pair<int,int>> queue;
    // mark the start location as visited
    visit[start.first][start.second]=true;
    //set the distance to the start to be 0
    length_of_path[start.first][start.second]=0;
    //encode the distance within the start location's lower order bits of the treasure map
    setLOB(*base_copy, start, 0);
    //enqueue the start location.
    queue.enqueue(start);
    pair<int,int> curr;
    vector<pair<int,int>>vec;
    pair<int,int> p;
    int i0=0,i1=0,i2=0,i3=0;
    while(!queue.isEmpty()){
        //a. set the current location, curr, to the value at the front of the queue (and dequeue).
        //      b. for each compass neighbor, p, of curr in the order of left, below, right, above:
        //          i. if p is "good" (defined below) then
        //              1) mark p's location as visited
        //              2) set p's distance to the start to be curr's distance, + 1.
        //              3) encode the distance in the lower order bits of the treasure map
        //              4) enqueue p
        curr=queue.dequeue();
        vec=neighbors(curr);
        p=vec[0];
        if(good(visit,curr,p)){
            visit[p.first][p.second]=true;
            length_of_path[p.first][p.second]= length_of_path[curr.first][curr.second]+1;
//            std::cout<<"check case 0 length_of_path value"<<endl;
//            std::cout<< length_of_path[curr.first][curr.second]<<endl;
//            std::cout<<length_of_path[p.first][p.second]<<endl;
            setLOB(*base_copy, p, length_of_path[p.first][p.second]);
            queue.enqueue(p);
            i0++;

        }
        p=vec[1];
        if(good(visit,curr,p)){
            visit[p.first][p.second]=true;
            length_of_path[p.first][p.second]= length_of_path[curr.first][curr.second]+1;
//            std::cout<<"check case 1 length_of_path value"<<endl;
//            std::cout<< length_of_path[curr.first][curr.second]<<endl;
//            std::cout<<length_of_path[p.first][p.second]<<endl;
            setLOB(*base_copy, p, length_of_path[p.first][p.second]);
            queue.enqueue(p);
            i1++;

        }
        p=vec[2];
        if(good(visit,curr,p)){
            visit[p.first][p.second]=true;
            length_of_path[p.first][p.second]= length_of_path[curr.first][curr.second]+1;
//            std::cout<<"check case 2 length_of_path value"<<endl;
//            std::cout<< length_of_path[curr.first][curr.second]<<endl;
//            std::cout<<length_of_path[p.first][p.second]<<endl;
            setLOB(*base_copy, p, length_of_path[p.first][p.second]);
            queue.enqueue(p);
            i2++;

        }
        p=vec[3];
        if(good(visit,curr,p)){
            visit[p.first][p.second]=true;
            length_of_path[p.first][p.second]= length_of_path[curr.first][curr.second]+1;
//            std::cout<<"check case 3 length_of_path value"<<endl;
//            std::cout<< length_of_path[curr.first][curr.second]<<endl;
//            std::cout<<length_of_path[p.first][p.second]<<endl;
            setLOB(*base_copy, p, length_of_path[p.first][p.second]);
            queue.enqueue(p);
            i3++;

        }

    }
//    std::cout<<i0<<endl;
//    std::cout<<i1<<endl;
//    std::cout<<i2<<endl;
//    std::cout<<i3<<endl;
//    length=length_of_path;
    //visits=visit;
    return *base_copy;
}

bool treasureMap::isEncoded(PNG & im,pair<int,int> curr, pair<int,int> next){
    //return true if the two positions on the im has distance 1 and are encoded, and they are within
    //the range and has the same color
//    unsigned char r= (im.getPixel(curr.first,curr.second)->r & 0b00000011) <<4;
//    unsigned char g= (im.getPixel(curr.first,curr.second)->g & 0b00000011) <<2;
//    unsigned char b= (im.getPixel(curr.first,curr.second)->b & 0b00000011);
//    unsigned char value =r|g|b;
//
//    unsigned char r_n= (im.getPixel(next.first,next.second)->r & 0b00000011) <<4;
//    unsigned char g_n= (im.getPixel(next.first,next.second)->g & 0b00000011) <<2;
//    unsigned char b_n= (im.getPixel(next.first,next.second)->b & 0b00000011);
//    unsigned char value_n=r_n|g_n|b_n;

    bool isWithinRange = next.first<im.width() && next.second<im.height() && next.first>= 0 && next.second >= 0;
    if(!isWithinRange)return false;
    bool isSameColor = (*maze.getPixel(curr.first,curr.second)==*maze.getPixel(next.first,next.second));
    bool isChanged= (*im.getPixel(next.first,next.second)!=*base.getPixel(next.first,next.second));
    bool isVisited= (visits[next.first][next.second]==true);

    //&& !isChanged
    if(  isSameColor  && !isVisited){
        //std::cout<<"169"<<endl;
        return true;
    }
    //std::cout<<"183"<<endl;
        return false;

}

PNG treasureMap::renderMaze(){
    // draws the entire maze on a copy of the base image by darkening the locations
    // so it's visible as a shadow. This can be done by iterating over every
    // pixel, but it will be faster to begin from the start position
    // and find the points in the maze from there. Returns an image whose
    // non-maze pixels are the same as the base image, and whose maze pixels
    // have colour values that are 50% of those in the base image, for each of
    // red, green and blue. (We specify the computation of the colours in the
    // description of a setGrey function, below.)

    PNG copy = renderMap();

    Queue<pair<int,int>> queue;
    queue.enqueue(start);
    vector<pair<int,int>> vec;
    pair<int,int> curr;
    pair<int,int> temp;
    visits[start.first][start.second]=true;
    int i0=0;
    int i1=0;
    int i2=0;
    int i3=0;

    while(!queue.isEmpty()){
        curr=queue.dequeue();
        vec=neighbors(curr);
        temp=vec[0];
        if(isEncoded(copy,curr,temp)){
            visits[temp.first][temp.second]=true;
            setGrey(copy,temp);
            queue.enqueue(temp);
            i0++;

        }
        temp=vec[1];
        if(isEncoded(copy,curr,temp)){
            visits[temp.first][temp.second]=true;
            setGrey(copy,temp);
            queue.enqueue(temp);
            i1++;
        }
        temp=vec[2];
        if(isEncoded(copy,curr,temp)){
            visits[temp.first][temp.second]=true;
            setGrey(copy,temp);
            queue.enqueue(temp);
            i2++;
        }
        temp=vec[3];
       if(isEncoded(*&copy,curr,temp)){
           visits[temp.first][temp.second]=true;
            setGrey(*&copy,temp);
            queue.enqueue(temp);
            i3++;
        }

   }


//
//    std::cout<<i0<<std::endl;
//    std::cout<<i1<<std::endl;
//    std::cout<<i2<<std::endl;
//    std::cout<<i3<<std::endl;

    // This function also draws a red 7px x 7px square at the start
    // location. If the start location is near the edge of the image,
    // just draw the existing portion of the square. The start
    // should be at the center of the square.


    int f1=start.first-3;
    if(f1<0){
        f1=0;
    }
    int f2=start.first+3;
    if(f2>=copy.width()){
        f2=copy.width()-1;
    }
    int s1=start.second-3;
    if(s1<0){
        s1=0;
    }
    int s2=start.second+3;
    if(s2>=copy.height()){
        s2=copy.height()-1;
    }
    for(int i=f1;i<=f2;i++){
        for(int j=s1;j<=s2;j++){
            copy.getPixel(i,j)->r=255;
            copy.getPixel(i,j)->g=0;
            copy.getPixel(i,j)->b=0;

        }
    }

    return copy;

}

bool treasureMap::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){
    // tests next, a neighbor (adjacent vertex) of curr to see if it is
    // 1. within the image, 2. unvisited, and 3. the same colour as curr in
    // the maze image (member var).  An entry in table v is true if a cell
    // has previously been visited, and false, otherwise. Colour sameness is
    // measured using the == operator on RGBAPixel values.


    bool isWithinRange = next.first<base.width() && next.second<base.height() && next.first>= 0 && next.second >= 0;
    if(!isWithinRange)return false;
    bool isVisited= (v[next.first][next.second]==false) &&(v[curr.first][curr.second]==true);
    bool isSameColor = *maze.getPixel(curr.first,curr.second)==*maze.getPixel(next.first,next.second);

    if(isVisited && isSameColor){
        return true;
    }
    return false;



}

vector<pair<int,int>> treasureMap::neighbors(pair<int,int> curr) {
    // builds a vector containing the locations of the
    // four vertices adjacent to curr:
    // left, below, right, above.
    // does not pay any attention to whether or not the neighbors are
    // valid (in the image, previously visited, or the right colour).

    vector<pair<int,int>> vec;
    pair<int,int> left;
    left.first=curr.first-1;
    left.second=curr.second;
    pair<int,int> below;
    below.first=curr.first;
    below.second=curr.second+1;
    pair<int,int> right;
    right.first=curr.first+1;
    right.second=curr.second;
    pair<int,int> above;
    above.first=curr.first;
    above.second=curr.second-1;
    vec.push_back(left);
    vec.push_back(below);
    vec.push_back(right);
    vec.push_back(above);
    return vec;
}

