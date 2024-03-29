#include <iostream>
#include <istream>
#include <fstream>
using namespace std;

typedef struct _square{
    int x;
    int y;
    char state;
    bool cleaned;
    int step;
} Square;

int row, col, battery;
void go_to_a_square(Square now, Square target);
void go_back(Square target, Square R);
Square R;
Square target;
int total_step = 0;
int dirty_square = 0;
Square back_way[1010][1010];
Square peta[1010][1010];
Square que[1010*1010];
const int dir[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};

ifstream input;
ofstream output;
ofstream tmp;

int main()
{
    input.open("floor.data");
    output.open("final.path");
    tmp.open("record.path");
    if(input.is_open()){
        input >> row >> col >> battery;

        int now_bat;
        Square now_pos, last_pos;
        int step_now=0;
        now_bat = battery;

        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                input >> (peta[i][j]).state;
                (peta[i][j]).y = i;
                (peta[i][j]).x = j;
                (peta[i][j]).cleaned = false;
                (peta[i][j]).step = 0;

                if((peta[i][j]).state == 'R'){
                    R = peta[i][j];
                    now_pos = peta[i][j];
                }
            }
        }

        int que_front=0, que_tail=0;
        que[que_front] = now_pos;
        que_front++;
        while(que_front > que_tail){
            Square curr = que[que_tail];
            que_tail++;
            for(int detect=0; detect<4; detect++){
                int tmp_x = curr.x + dir[detect][1];
                int tmp_y = curr.y + dir[detect][0];
                if(tmp_x<0 || tmp_x>=col || tmp_y<0 || tmp_y>=row){
                    continue;
                }
                Square next = peta[tmp_y][tmp_x];
                if(next.state == '1'|| next.state=='R')
                    continue;
                else if(next.state=='0' && next.step==0){
                    que[que_front] = next;
                    que_front++;
                    peta[tmp_y][tmp_x].step = peta[curr.y][curr.x].step + 1;
                    back_way[tmp_y][tmp_x] = curr;
                }
            }
        }

        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                if(peta[i][j].state == '0' && peta[i][j].cleaned==false)
                    dirty_square++;
            }
        }

        while(dirty_square!=0){
            int max_step = -10;
            for(int i=0;i<row;i++){
                for(int j=0;j<col;j++){
                    if(peta[i][j].step > max_step && peta[i][j].state=='0' && peta[i][j].cleaned==false){
                        max_step = peta[i][j].step;
                        target = peta[i][j];
                    }
                }
            }
            if(peta[target.y][target.x].cleaned==true)
                break;
            total_step += 2*target.step;
            go_to_a_square(target, now_pos);
            go_back(target, R);
        }
        tmp.close();
    }
    input.close();
    output << total_step << endl;
    output << R.y << " " << R.x << endl;
    ifstream tmp_in;
    tmp_in.open("record.path");

    int x, y;
    for(int i=0;i<total_step;i++){
        tmp_in >> y >> x;
        output << y << " " << x << endl;
    }
    tmp_in.close();
    output.close();
    return 0;
}

void go_to_a_square(Square now, Square target){
	if((now.x==target.x) && (now.y==target.y)){
		return;
	}
	else{
        go_to_a_square(back_way[now.y][now.x], target);
		if(now.state == '0' && peta[now.y][now.x].cleaned==false){
			peta[now.y][now.x].cleaned = true;
			dirty_square--;
		}
		tmp << now.y << ' ' << now.x << endl;
	}
}

void go_back(Square target, Square R)
{
    Square curr=target;
    Square next;
    Square real_next = R;
    while(1)
    {
        for(int detect=0; detect<4; detect++){
            int tmp_x = curr.x + dir[detect][1];
            int tmp_y = curr.y + dir[detect][0];
            if(tmp_x<0 || tmp_x>=col || tmp_y<0 || tmp_y>=row){
                continue;
            }
            next = peta[tmp_y][tmp_x];
            if(next.step >= curr.step){
                continue;
            }
            if(next.state == '1'|| next.state=='R')
                continue;
            else if(next.state=='0' && next.cleaned==false){
                real_next = next;
                peta[next.y][next.x].cleaned = true;
                break;
            }
            else if(next.state=='0'){
                real_next = next;
            }
        }
        if((real_next.y != R.y) || (real_next.x!=R.x)){
            curr = real_next;
            tmp << curr.y << ' ' << curr.x << endl;
        }
        if((curr.y==R.y-1 && curr.x==R.x) || (curr.y==R.y+1 && curr.x==R.x) || (curr.y==R.y && curr.x==R.x-1) || (curr.y==R.y && curr.x==R.x+1))
        {
            break;
        }
    }
    tmp << R.y << ' ' << R.x << endl;
    return;
}
