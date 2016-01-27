#include <iostream>
#include "core.h"
#include <iterator>
#include <bumpcheck_extra/square.h>
#include <sstream>

using boost::filesystem::path;
using boost::filesystem::ifstream;
using std::istreambuf_iterator;
using ::item::pos;
using ::item::square;
using boost::property_tree::ini_parser::read_ini;
namespace core{
map_manager::map_manager(boost::filesystem::path ini_file)
{
	read_ini(ini_file.string(), map_tree);
}

void map_manager::read_map(path file,std::vector<ritem> &items)
{
	ifstream f(file);
	istreambuf_iterator<char> start(f),end;
	int n;
	int size=map_tree.get<int>("block.size");
	int width=map_tree.get<int>("block.width");
	int lenth=map_tree.get<int>("block.lenth");
	int bsize=size<<1;
	unsigned char state;
	for(int i=0;i<width;i++){
		for(int j=0;j<lenth;j++){
			n=*start++;
			std::stringstream a;
			a<<n;
			a<<".type";
			switch(map_tree.get<int>(a.str())){
				case 1:
				state=*start++;
				if(state&0x4)
				{
					items.push_back(ritem(item::pos(i*bsize,j*bsize),size,size,n));
					items.push_back(ritem(item::pos(i*bsize+size,j*bsize),size,size,n));
					items.push_back(ritem(item::pos(i*bsize,j*bsize+size),size,size,n));
					items.push_back(ritem(item::pos(i*bsize+size,j*bsize+size),size,size,n));
				}
				else
				{
					if((state&0x1)==0)
					{
						items.push_back(ritem(item::pos(i*bsize,j*bsize),size,size,n));
					}
					else
					{
						items.push_back(ritem(item::pos(i*bsize+size,j*bsize+size),size,size,n));
					}
					state++;
					if(state&0x2)
					{
						items.push_back(ritem(item::pos(i*bsize,j*bsize+size),size,size,n));
					}
					else
					{
						items.push_back(ritem(item::pos(i*bsize+size,j*bsize),size,size,n));
					}
				}
				break;
				case 0:
					items.push_back(ritem(item::pos(i*bsize,j*bsize),bsize,bsize,n));
				break;
				case 2:
				break;
			}
		}
	}
}
ritem::ritem(pos pos_, int lenth, int width,int type_):square(pos_,lenth,width),type(type_)
{
}
}