#include <iostream>
#include <string>
#include <istream>
#include <cstring>
#include <fstream>

using namespace std;

typedef struct _square{
    int x;
    int y;
    char state;
    bool cleaned;
    int step;
    int step_tmp;
    bool visited;
    int dir_to_walk;
} Square;

int main()
{
    ifstream input;
    ofstream output;
    input.open("floor.data");
    output.open("final.path");

    int row, col, battery;

    if(input.is_open()){
        input >> row >> col >> battery;
        cout << row << ' ' << col << ' ' << battery << '\n';

        Square peta[row][col];
        int R_row, R_col;
        Square R;
        int target_row, target_col;
        int now_bat;
        Square now_pos, last_pos;
        int step_now=0;
        now_bat = battery;
        const int dir[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        Square que[row*col];
        int dirty_square=0;

        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                input >> (peta[i][j]).state;
                (peta[i][j]).y = i;
                (peta[i][j]).x = j;
                (peta[i][j]).cleaned = false;
                (peta[i][j]).step = 0;
                (peta[i][j]).step_tmp = -1;
                (peta[i][j]).dir_to_walk = 0;
                (peta[i][j]).visited = false;
                if((peta[i][j]).state == 'R'){
                    R = peta[i][j];
                    now_pos = peta[i][j];
                }
            }
        }
        //cout << now_row << " " << now_col << endl;

        for(int i=1; i<row-1; i++){
            for(int j=1; j<col-1; j++){
                if(peta[i][j].state == '1'|| peta[i][j].state=='R')
                    continue;
                dirty_square++;
                for(int detect=0; detect<4; detect++){
                    int tmp_x = (peta[i][j]).x + dir[detect][1];
                    int tmp_y = (peta[i][j]).y + dir[detect][0];
                    //cout << "col: " << tmp_x << "  row: " << tmp_y << endl;
                    if(tmp_x<0 || tmp_x>=col || tmp_y<0 || tmp_y>=row){
                        continue;
                    }
                    Square next = peta[tmp_y][tmp_x];
                    //cout << "next: " << next.state << endl;
                    if(next.state == '1'|| next.state=='R')
                        continue;
                    else if(next.state=='0'){
                        //peta[tmp_y][tmp_x].step = peta[i][j].step + 1;
                        peta[i][j].dir_to_walk++;
                        //cout << "peta[" << i << "][" << j << "].dir_to_walk = " << peta[i][j].dir_to_walk << endl;
                    }
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
                cout << "col: " << tmp_x << "  row: " << tmp_y << endl;
                if(tmp_x<0 || tmp_x>=col || tmp_y<0 || tmp_y>=row){
                    continue;
                }
                Square next = peta[tmp_y][tmp_x];
                cout << "next: " << next.state << endl;
                if(next.state == '1'|| next.state=='R')
                    continue;
                else if(next.state=='0' && next.step==0){
                    que[que_front] = next;
                    que_front++;
                    peta[tmp_y][tmp_x].step = peta[curr.y][curr.x].step + 1;
                    //cout << "peta[" << i << "][" << j << "].dir_to_walk = " << peta[i][j].dir_to_walk << endl;
                }
            }
        }

        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                if(peta[i][j].state=='0')
                    cout << (peta[i][j]).step << " ";
                else
                    cout << "X ";
            }
            cout << endl;
        }

        Square target = now_pos;
        int max_step=0;
        int min_step=row*col;
        int min_dir_to_walk=5;
        bool need_charge=false;
        bool found=false;
        bool ended=false;

        while(1){
            need_charge=false;
            found=false;
            ended=false;
            if(target==now_pos){
                min_step = now_pos.step;
                for(int detect=0; detect<4; detect++){
                    int tmp_x = now_pos.x + dir[detect][1];
                    int tmp_y = now_pos.y + dir[detect][0];
                    if(tmp_x<0 || tmp_x>=col || tmp_y<0 || tmp_y>=row || peta[tmp_y][tmp_x].state=='1'){
                        continue;
                    }
                    Square next = peta[tmp_y][tmp_x];
                    if(next.step < min_step){
                        min_step = next.step;
                        target = next;
                        if(target.cleaned){
                            min_dir_to_walk = 5;
                        }
                        else{
                            min_dir_to_walk = target.dir_to_walk;
                        }
                    }
                    else if(next.step == min_step){
                        if(next.dir_to_walk < min_dir_to_walk && next.cleaned==false){
                            min_step = next.step;
                            taregt = next;
                            min_dir_to_walk = target.dir_to_walk;
                        }
                    }
                }
            }
        }
            for(int i=1; i<row-1; i++){
                for(int j=1; j<col-1; j++){
                    if(peta[i][j].state == '1'|| peta[i][j].state=='R')
                        continue;
                    for(int detect=0; detect<4; detect++){
                        int tmp_x = (peta[i][j]).x + dir[detect][1];
                        int tmp_y = (peta[i][j]).y + dir[detect][0];
                        //cout << "col: " << tmp_x << "  row: " << tmp_y << endl;
                        if(tmp_x<0 || tmp_x>=col || tmp_y<0 || tmp_y>=row){
                            continue;
                        }
                        Square next = peta[tmp_y][tmp_x];
                        //cout << "next: " << next.state << endl;
                        if(next.state == '1'|| next.state=='R')
                            continue;
                        else if(next.state=='0'){
                            //peta[tmp_y][tmp_x].step = peta[i][j].step + 1;
                            peta[i][j].dir_to_walk++;
                            //cout << "peta[" << i << "][" << j << "].dir_to_walk = " << peta[i][j].dir_to_walk << endl;
                        }
                    }
                }
            }
            ended = false;
        }
        if(now_pos.cleaned==false){
            now_pos.cleaned = true;
            dirty_square--;
        }
        if(ended==false){
            last_pos = now_pos;
        }
        now_bat--;
        if(now_pos==R){
            now_bat = battery;
            if(ended==true){
                for(int i=0; i<row; i++){
                    for(int j=0; j<col; j++){
                        input >> (peta[i][j]).state;
                        (peta[i][j]).y = i;
                        (peta[i][j]).x = j;
                        (peta[i][j]).cleaned = false;
                        (peta[i][j]).step = 0;
                        (peta[i][j]).step_tmp = -1;
                        (peta[i][j]).dir_to_walk = 0;
                        (peta[i][j]).visited = false;
                        if((peta[i][j]).state == 'R'){
                            R = peta[i][j];
                            now_pos = peta[i][j];
                        }
                    }
                }
            //cout << now_row << " " << now_col << endl;

                for(int i=1; i<row-1; i++){
                    for(int j=1; j<col-1; j++){
                        if(peta[i][j].state == '1'|| peta[i][j].state=='R')
                            continue;
                        for(int detect=0; detect<4; detect++){
                            int tmp_x = (peta[i][j]).x + dir[detect][1];
                            int tmp_y = (peta[i][j]).y + dir[detect][0];
                            //cout << "col: " << tmp_x << "  row: " << tmp_y << endl;
                            if(tmp_x<0 || tmp_x>=col || tmp_y<0 || tmp_y>=row){
                                continue;
                            }
                            Square next = peta[tmp_y][tmp_x];
                            //cout << "next: " << next.state << endl;
                            if(next.state == '1'|| next.state=='R')
                                continue;
                            else if(next.state=='0'){
                                //peta[tmp_y][tmp_x].step = peta[i][j].step + 1;
                                peta[i][j].dir_to_walk++;
                                //cout << "peta[" << i << "][" << j << "].dir_to_walk = " << peta[i][j].dir_to_walk << endl;
                            }
                        }
                    }
                }
            }
        }
    }
    input.close();
    return 0;
}
