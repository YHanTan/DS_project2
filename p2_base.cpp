#include <iostream>
#include <string>
#include <istream>
#include <cstring>
#include <fstream>

using namespace std;
const int count_road=0;

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

        char peta[row][col];
        //int done[row][col]; //-10: robot -5: wall 1: done
        int R_row, R_col;
        int target_row, target_col;
        int now_row, now_col, now_bat;
        int step_now=0;
        now_bat = battery;
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                peta[i][j]=0;
            }
        }
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                input >> peta[i][j];
                if(peta[i][j]=='R'){
                    R_row = i;
                    R_col = j;
                    now_row = i;
                    now_col = j;
                }
            }
        }
        cout << now_row << " " << now_col << endl;

        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                cout << peta[i][j] << " ";
            }
            cout << endl;
        }

        int target_flag=0;
        int flag=0, once=0;
        int min_bat=0;
        int go_back=0;

        while(1){
            int a, b;
            for(a=1; a<row-1; a++){
                for(b=1; b<col-1; b++){
                    //cout << "flag: " << flag << endl;
                    if(peta[a][b]=='0'){
                        target_col = b;
                        target_row = a;
                        flag=1;
                        break;
                    }
                }
                if(flag)
                    break;
            }
            if(b==col-1 && a==row-1){
                if(peta[a-1][b-1]!='0')
                    break;
            }
            min_bat = (target_col-R_col) + (target_row-R_row);
            while(1){
                for(int i=0; i<row; i++){
                    for(int j=0; j<col; j++){
                        if(i==now_row && j==now_col)
                            cout << "W" << " ";
                        else if(i==target_row && j==target_col)
                            cout << "T" << " ";
                        else
                            cout << peta[i][j] << " ";
                    }
                    cout << endl;
                }
                cout << "target: " << target_row << " " << target_col << endl;
                if(now_row > target_row){
                    if(peta[now_row-1][now_col]!='1'){
                        peta[now_row-1][now_col] = 'D';
                        now_row--;
                        now_bat--;
                    }
                    else if(now_col > target_col){
                        if(peta[now_row][now_col-1]!='1'){
                            peta[now_row][now_col-1] = 'D';
                            now_col--;
                            now_bat--;
                        }
                    }
                    else if(now_col < target_col){
                        if(peta[now_row][now_col+1]!='1'){
                            peta[now_row+1][now_col] = 'D';
                            now_col++;
                            now_bat--;
                        }
                    }
                }
                else if(now_row < target_row){
                    if(peta[now_row+1][now_col]!='1'){
                        peta[now_row+1][now_col] = 'D';
                        now_row++;
                        now_bat--;
                    }
                    else if(now_col > target_col){
                        if(peta[now_row][now_col-1]!='1'){
                            peta[now_row][now_col-1] = 'D';
                            now_col--;
                            now_bat--;
                        }
                    }
                    else if(now_col < target_col){
                        if(peta[now_row][now_col+1]!='1'){
                            peta[now_row+1][now_col] = 'D';
                            now_col++;
                            now_bat--;
                        }
                    }
                }
                else if(now_col < target_col){
                    if(peta[now_row][now_col+1]!='1'){
                        peta[now_row][now_col+1] = 'D';
                        now_col++;
                        now_bat--;
                    }
                    else if(now_col > target_col){
                        if(peta[now_row][now_col-1]!='1'){
                            peta[now_row][now_col-1] = 'D';
                            now_col--;
                            now_bat--;
                        }
                    }
                    else if(now_col < target_col){
                        if(peta[now_row][now_col+1]!='1'){
                            peta[now_row+1][now_col] = 'D';
                            now_col++;
                            now_bat--;
                        }
                    }
                }
            }
            while(1){
                for(int i=0; i<row; i++){
                    for(int j=0; j<col; j++){
                        if(i==now_row && j==now_col)
                            cout << "W" << " ";
                        else if(i==target_row && j==target_col)
                            cout << "T" << " ";
                        else
                            cout << peta[i][j] << " ";
                    }
                    cout << endl;
                }
                cout << "target: " << target_row << " " << target_col << endl;
                if(target_row >= now_row && target_col >= now_col){
                    //R D L U
                    if(peta[now_row][now_col+1]=='0'){
                        peta[now_row][now_col+1] = 'D';
                        now_col++;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row+1][now_col]=='0'){
                        peta[now_row+1][now_col] = 'D';
                        now_row++;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row][now_col-1]=='0'){
                        peta[now_row][now_col-1] = 'D';
                        now_col--;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row-1][now_col]=='0'){
                        peta[now_row-1][now_col] = 'D';
                        now_row--;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row][now_col+1]=='D' || peta[now_row][now_col+1]=='R'){
                        now_col++;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row+1][now_col]=='D' || peta[now_row+1][now_col]=='R'){
                        now_row++;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row][now_col-1]=='D' || peta[now_row][now_col-1]=='R'){
                        now_col--;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row-1][now_col]=='D' || peta[now_row-1][now_col]=='R'){
                        now_row--;
                    }
                    now_bat--;
                    step_now++;
                    cout << now_row << " " << now_col << endl;
                }

                else if(target_row >= now_row && target_col <= now_col){
                    //L D R U
                    if(peta[now_row][now_col-1]=='0'){
                        peta[now_row][now_col-1] = 'D';
                        now_col--;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row+1][now_col]=='0'){
                        peta[now_row+1][now_col] = 'D';
                        now_row++;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row][now_col+1]=='0'){
                        peta[now_row][now_col+1] = 'D';
                        now_col++;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row-1][now_col]=='0'){
                        now_row--;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row][now_col-1]=='D' || peta[now_row][now_col-1]=='R'){
                        now_col--;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row+1][now_col]=='D' || peta[now_row+1][now_col]=='R'){
                        now_row++;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row][now_col+1]=='D' || peta[now_row][now_col+1]=='R'){
                        now_col++;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row-1][now_col]=='D' || peta[now_row-1][now_col]=='R'){
                        now_row--;
                    }
                    now_bat--;
                    step_now++;
                    cout << now_row << " " << now_col << endl;
                }

                else if(target_row <= now_row && target_col >= now_col){
                    //R U L D
                    if(peta[now_row][now_col+1]=='0'){
                        peta[now_row][now_col+1] = 'D';
                        now_col++;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row-1][now_col]=='0'){
                        peta[now_row-1][now_col] = 'D';
                        now_row--;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row][now_col-1]=='0'){
                        peta[now_row][now_col-1] = 'D';
                        now_col--;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row+1][now_col]=='0'){
                        peta[now_row+1][now_col] = 'D';
                        now_row++;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row][now_col+1]=='D' || peta[now_row][now_col+1]=='R'){
                        now_col++;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row-1][now_col]=='D' || peta[now_row-1][now_col]=='R'){
                        now_row--;
                    }
                    else if(peta[now_row][now_col-1]=='D' || peta[now_row][now_col-1]=='R'){
                        now_col--;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row+1][now_col]=='D' || peta[now_row+1][now_col]=='R'){
                        now_row++;
                        //cout << now_row << " " << now_col << endl;
                    }

                    now_bat--;
                    step_now++;
                    cout << now_row << " " << now_col << endl;
                }

                else if(target_row <= now_row && target_col <= now_col){
                    //L U R D
                    if(peta[now_row][now_col-1]=='0'){
                        peta[now_row][now_col-1] = 'D';
                        now_col--;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row-1][now_col]=='0'){
                        peta[now_row-1][now_col] = 'D';
                        now_row--;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row][now_col+1]=='0'){
                        peta[now_row][now_col+1] = 'D';
                        now_col++;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row+1][now_col]=='0'){
                        peta[now_row+1][now_col] = 'D';
                        now_row++;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row][now_col-1]=='D' || peta[now_row][now_col-1]=='R'){
                        now_col--;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row-1][now_col]=='D' || peta[now_row-1][now_col]=='R'){
                        now_row--;
                    }
                    else if(peta[now_row][now_col+1]=='D' || peta[now_row][now_col+1]=='R'){
                        now_col++;
                        //cout << now_row << " " << now_col << endl;
                    }
                    else if(peta[now_row+1][now_col]=='D' || peta[now_row+1][now_col]=='R'){
                        now_row++;
                        //cout << now_row << " " << now_col << endl;
                    }
                    now_bat--;
                    step_now++;
                    cout << now_row << " " << now_col << endl;
                }
                if(step_now >= now_bat){
                    go_back=1;
                }
                if(now_bat < min_bat || (now_row==target_row && now_col==target_col)){
                    //target_flag = 1;
                    target_row = R_row;
                    target_col = R_col;
                    min_bat = (target_col-R_col) + (target_row-R_row);
                    once = 1;
                    //break;
                }
                if(go_back){
                    if(now_col > R_col){
                        if(peta[row][now_col-1])
                        {
                            now_col--;
                            now_bat--;
                        }
                    }
                }
                if(now_col==R_col && now_row==R_row)
                    now_bat = battery;
                cout << "battery: " << now_bat << endl;
                if(once==1 && (now_row==target_row && now_col==target_col))
                    break;
            }
        }
    }
    input.close();
    return 0;
}
