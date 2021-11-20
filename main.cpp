#include<bits/stdc++.h>
#define TIGERWIN 2147483647
#define GOATWIN -2147483647
#define DRAW 0
#define MAXDEPTH 8
#define EMPTY_SPACE '*'
using namespace std;

vector<pair<int,int> >capture[25];
vector<pair<int,int> > node;

char grid[9][9]= {{'G','_','G','_','G','_','G', '_', 'T'},{'|','\\','|','/','|','\\','|','/','|'},{'G','_','G','_','G','_','*','_','G'},{'|','/','|','\\','|','/','|','\\','|'},{'G','_','G','_','G','_','T','_','G'},{'|','\\','|','/','|','\\','|','/','|'},{'G','_','G','_','T','_','G','_','G'},{'|','/','|','\\','|','/','|','\\','|'},{'T','_','G','_','G','_','G','_','G'}};
char arr[9][9]= {{'A','_','B','_','C','_','D', '_', 'E'},{'|','\\','|','/','|','\\','|','/','|'},{'F','_','G','_','H','_','I','_','J'},{'|','/','|','\\','|','/','|','\\','|'},{'K','_','L','_','M','_','N','_','O'},{'|','\\','|','/','|','\\','|','/','|'},{'P','_','Q','_','R','_','S','_','T'},{'|','/','|','\\','|','/','|','\\','|'},{'U','_','V','_','W','_','X','_','Y'}};
///char grid[9][9]= {{'G','_','G','_','G','_','G', '_', 'G'},{'|','\\','|','/','|','\\','|','/','|'},{'G','_','T','_','G','_','T','_','G'},{'|','/','|','\\','|','/','|','\\','|'},{'G','_','G','_','*','_','G','_','G'},{'|','\\','|','/','|','\\','|','/','|'},{'G','_','T','_','G','_','T','_','G'},{'|','/','|','\\','|','/','|','\\','|'},{'G','_','G','_','G','_','G','_','G'}};

map<pair<int,int>, int>mp1;

map<int,pair<int,int> >mp2;

vector<pair<int,int> >edge;

vector<int>adjList[25];

vector<int>GOAT(20);

vector<int>node_to_goat(25,-1);

vector<int> Tiger(4);

vector<int>node_to_tiger(25,-1);


int numOfGoat = 20;

void show_grid(void)
{
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            printf("%c ",grid[i][j]);
        }
        printf("              ");
        for(int j=0; j<9; j++)
        {
            printf("%c ",arr[i][j]);
        }
        printf("\n");
    }
}

bool isTheCellEmpty(int cell)
{
    int x = mp2[cell].first;
    int y = mp2[cell].second;
    return (grid[x][y]=='*');
}

bool isTheMoveValid(int from, int to)
{
    for(auto it:adjList[from])
        if(it==to)
            return true;
    return false;
}

bool isCaptured(int val1, int val2, int* val)
{
    *val = -1;
    if(!isTheCellEmpty(val2))
        return false;
    for(auto it:capture[val1])
    {
        if(it.first==val2 && grid[mp2[it.second].first][mp2[it.second].second]=='G')
        {
            *val=it.second;
            return true;
        }
    }
    return false;
}

void initiateEverything(void)
{
    Tiger[0] = 4;
    Tiger[1] = 13;
    Tiger[2] = 17;
    Tiger[3] = 20;

    node_to_tiger[4]=0;
    node_to_tiger[13]=1;
    node_to_tiger[17]=2;
    node_to_tiger[20]=3;


    capture[0].push_back({2,1});
    capture[0].push_back({10,5});
    capture[0].push_back({12,6});
    capture[1].push_back({3,2});
    capture[1].push_back({11,6});
    capture[2].push_back({4,3});
    capture[2].push_back({0,1});
    capture[2].push_back({12,7});
    capture[2].push_back({14,8});
    capture[2].push_back({10,6});
    capture[3].push_back({1,2});
    capture[3].push_back({13,8});
    capture[4].push_back({2,3});
    capture[4].push_back({14,9});
    capture[4].push_back({12,8});
    capture[5].push_back({15,10});
    capture[5].push_back({7,6});
    capture[6].push_back({8,7});
    capture[6].push_back({16,11});
    capture[6].push_back({18,12});
    capture[7].push_back({5,6});
    capture[7].push_back({9,8});
    capture[7].push_back({17,12});
    capture[8].push_back({6,7});
    capture[8].push_back({18,13});
    capture[8].push_back({16,12});
    capture[9].push_back({19,14});
    capture[9].push_back({7,8});
    capture[10].push_back({0,5});
    capture[10].push_back({20,15});
    capture[10].push_back({12,11});
    capture[10].push_back({2,6});
    capture[10].push_back({22,16});
    capture[11].push_back({1,6});
    capture[11].push_back({21,16});
    capture[11].push_back({13,12});
    capture[12].push_back({0,6});
    capture[12].push_back({2,7});
    capture[12].push_back({4,8});
    capture[12].push_back({14,13});
    capture[12].push_back({24,18});
    capture[12].push_back({22,17});
    capture[12].push_back({20,16});
    capture[12].push_back({10,11});
    capture[13].push_back({3,8});
    capture[13].push_back({11,12});
    capture[13].push_back({23,18});
    capture[14].push_back({4,1});
    capture[14].push_back({24,19});
    capture[14].push_back({12,13});
    capture[14].push_back({2,8});
    capture[14].push_back({22,18});
    capture[15].push_back({5,10});
    capture[15].push_back({17,16});
    capture[16].push_back({6,11});
    capture[16].push_back({8,12});
    capture[16].push_back({18,17});
    capture[17].push_back({15,16});
    capture[17].push_back({19,18});
    capture[17].push_back({7,12});
    capture[18].push_back({16,17});
    capture[18].push_back({6,12});
    capture[18].push_back({8,13});
    capture[19].push_back({9,14});
    capture[19].push_back({17,18});
    capture[20].push_back({10,15});
    capture[20].push_back({12,16});
    capture[20].push_back({22,21});
    capture[21].push_back({11,16});
    capture[21].push_back({23,22});
    capture[22].push_back({20,21});
    capture[22].push_back({24,23});
    capture[22].push_back({10,16});
    capture[22].push_back({14,18});
    capture[22].push_back({12,17});
    capture[23].push_back({13,18});
    capture[23].push_back({21,22});
    capture[24].push_back({14,19});
    capture[24].push_back({12,18});
    capture[24].push_back({22,23});

    node.push_back({0,0});
    node.push_back({0,2});
    node.push_back({0,4});
    node.push_back({0,6});
    node.push_back({0,8});
    node.push_back({2,0});
    node.push_back({2,2});
    node.push_back({2,4});
    node.push_back({2,6});
    node.push_back({2,8});
    node.push_back({4,0});
    node.push_back({4,2});
    node.push_back({4,4});
    node.push_back({4,6});
    node.push_back({4,8});
    node.push_back({6,0});
    node.push_back({6,2});
    node.push_back({6,4});
    node.push_back({6,6});
    node.push_back({6,8});
    node.push_back({8,0});
    node.push_back({8,2});
    node.push_back({8,4});
    node.push_back({8,6});
    node.push_back({8,8});

    for(int i=0; i<node.size(); i++)
        mp1[node[i]]=i,mp2[i]=node[i];

    edge.push_back({0, 1});
    edge.push_back({1, 0});
    edge.push_back({1, 2});
    edge.push_back({2, 1});
    edge.push_back({2, 3});
    edge.push_back({3, 2});
    edge.push_back({3, 4});
    edge.push_back({4, 3});
    edge.push_back({0, 5});
    edge.push_back({5, 0});
    edge.push_back({0, 6});
    edge.push_back({6, 0});
    edge.push_back({1, 6});
    edge.push_back({6, 1});
    edge.push_back({2, 6});
    edge.push_back({6, 2});
    edge.push_back({2, 7});
    edge.push_back({7, 2});
    edge.push_back({2, 8});
    edge.push_back({8, 2});
    edge.push_back({3, 8});
    edge.push_back({8, 3});
    edge.push_back({4, 8});
    edge.push_back({8, 4});
    edge.push_back({4, 9});
    edge.push_back({9, 4});
    edge.push_back({5, 6});
    edge.push_back({6, 5});
    edge.push_back({6, 7});
    edge.push_back({7, 6});
    edge.push_back({7, 8});
    edge.push_back({8, 7});
    edge.push_back({8, 9});
    edge.push_back({9, 8});
    edge.push_back({5, 10});
    edge.push_back({10, 5});
    edge.push_back({6, 10});
    edge.push_back({10, 6});
    edge.push_back({6, 11});
    edge.push_back({11, 6});
    edge.push_back({6, 12});
    edge.push_back({12, 6});
    edge.push_back({7, 12});
    edge.push_back({12, 7});
    edge.push_back({8, 12});
    edge.push_back({12, 8});
    edge.push_back({8, 13});
    edge.push_back({13, 8});
    edge.push_back({8, 14});
    edge.push_back({14, 8});
    edge.push_back({9, 14});
    edge.push_back({14, 9});
    edge.push_back({10, 11});
    edge.push_back({11, 10});
    edge.push_back({11, 12});
    edge.push_back({12, 11});
    edge.push_back({12, 13});
    edge.push_back({13, 12});
    edge.push_back({13, 14});
    edge.push_back({14, 13});
    edge.push_back({10, 15});
    edge.push_back({15, 10});
    edge.push_back({10, 16});
    edge.push_back({16, 10});
    edge.push_back({11, 16});
    edge.push_back({16, 11});
    edge.push_back({12, 16});
    edge.push_back({16, 12});
    edge.push_back({12, 17});
    edge.push_back({17, 12});
    edge.push_back({12, 18});
    edge.push_back({18, 12});
    edge.push_back({13, 18});
    edge.push_back({18, 13});
    edge.push_back({14, 18});
    edge.push_back({18, 14});
    edge.push_back({14, 19});
    edge.push_back({19, 14});
    edge.push_back({15, 16});
    edge.push_back({16, 15});
    edge.push_back({16, 17});
    edge.push_back({17, 16});
    edge.push_back({17, 18});
    edge.push_back({18, 17});
    edge.push_back({18, 19});
    edge.push_back({19, 18});
    edge.push_back({15, 20});
    edge.push_back({20, 15});
    edge.push_back({16, 20});
    edge.push_back({20, 16});
    edge.push_back({16, 21});
    edge.push_back({21, 16});
    edge.push_back({16, 22});
    edge.push_back({22, 16});
    edge.push_back({17, 22});
    edge.push_back({22, 17});
    edge.push_back({18, 22});
    edge.push_back({22, 18});
    edge.push_back({18, 23});
    edge.push_back({23, 18});
    edge.push_back({18, 24});
    edge.push_back({24, 18});
    edge.push_back({19, 24});
    edge.push_back({24, 19});
    edge.push_back({20, 21});
    edge.push_back({21, 20});
    edge.push_back({21, 22});
    edge.push_back({22, 21});
    edge.push_back({22, 23});
    edge.push_back({23, 22});
    edge.push_back({23, 24});
    edge.push_back({24, 23});

    for(auto it:edge)
        adjList[it.first].push_back(it.second);




    GOAT[0] = 0;
    node_to_goat[0] = 0;
    GOAT[1] = 1;
    node_to_goat[1] = 1;
    GOAT[2] = 2;
    node_to_goat[2] = 2;
    GOAT[3] = 3;
    node_to_goat[3] = 3;
    GOAT[4] = 5;
    node_to_goat[5] = 4;
    GOAT[5] = 6;
    node_to_goat[6] = 5;
    GOAT[6] = 7;
    node_to_goat[7] = 6;
    GOAT[7] = 9;
    node_to_goat[9] = 7;
    GOAT[8] = 10;
    node_to_goat[10] = 8;
    GOAT[9] = 11;
    node_to_goat[11] = 9;
    GOAT[10] = 12;
    node_to_goat[12] = 10;
    GOAT[11] = 14;
    node_to_goat[14] = 11;
    GOAT[12] = 15;
    node_to_goat[15] = 12;
    GOAT[13] = 16;
    node_to_goat[16] = 13;
    GOAT[14] = 18;
    node_to_goat[18] = 14;
    GOAT[15] = 19;
    node_to_goat[19] = 15;
    GOAT[16] = 21;
    node_to_goat[21] = 16;
    GOAT[17] = 22;
    node_to_goat[22] = 17;
    GOAT[18] = 23;
    node_to_goat[23] = 18;
    GOAT[19] = 24;
    node_to_goat[24] = 19;





    numOfGoat = 20;


    for(int i=0; i<20; i++)
    {

        pair<int,int> p = mp2[GOAT[i]];
        grid[p.first][p.second] = 'G';
    }

    for(int i=0; i<4; i++)
    {
        pair<int,int> p = mp2[Tiger[i]];
        grid[p.first][p.second] = 'T';
    }

}
bool isThereAnyPossibleMoveExistsForTiger(void)
{
    for(int i=0; i<4; i++)
    {
        for(auto it:adjList[Tiger[i]])
        {
            if(isTheCellEmpty(it))
                return true;
        }
    }

    for(int i=0; i<4; i++)
    {
        for(auto it:capture[Tiger[i]])
        {
            int val = -1;
            if(isCaptured(Tiger[i],it.first,&val))
                return true;
        }
    }

    return false;
}

bool isThereAnyPossibleMoveExistsForGoat(void)
{
    for(int i=0; i<20; i++)
    {
        int nodex = GOAT[i];
        if(nodex<0)
            continue;
        for(auto it:adjList[nodex])
        {
            if(isTheCellEmpty(it))
                return true;
        }

    }
    return false;
}


bool isGameOver(bool tigerMove)
{
    if(tigerMove)
    {
        if(!isThereAnyPossibleMoveExistsForTiger())
            return true;
    }
    else
    {
        if(!isThereAnyPossibleMoveExistsForGoat())
            return true;
    }
    return false;
}









vector < pair <int, int> > possibleMoves(bool tigerTurn)
{
    vector < pair <int, int> > moves;

    if(tigerTurn)
    {
        for(int i=0; i<4; i++)
        {
            for(int j = 0; j < capture[Tiger[i]].size(); j++)
            {
                int x = capture[Tiger[i]][j].first;
                int y = capture[Tiger[i]][j].second;

                if(grid[mp2[x].first][mp2[x].second] == '*' && grid[mp2[y].first][mp2[y].second] == 'G')
                    moves.push_back({Tiger[i],x});

            }

            for(int j = 0; j < adjList[Tiger[i]].size(); j++)
            {
                int x = adjList[Tiger[i]][j];
                if(grid[mp2[x].first][mp2[x].second] == '*')
                    moves.push_back({Tiger[i],x});

            }
        }
    }
    else
    {
        for(int i = 0; i < 20; i++)
        {
            int cPoG = GOAT[i];

            if(cPoG != -1)
            {
                for(int j = 0; j < adjList[cPoG].size(); j++)
                {
                    int x = adjList[cPoG][j];
                    if(grid[mp2[x].first][mp2[x].second] == '*')
                        moves.push_back({cPoG,x});

                }
            }
        }
    }

    return moves;
}













pair<int, pair<int,int> > minimax_optimization(bool tigersTurn, int depth, int alpha, int beta)
{


    pair<int,int> best_move = make_pair(-1,-1);
    int best_score = (tigersTurn) ? GOATWIN : TIGERWIN;

    if (isGameOver(tigersTurn) || depth==MAXDEPTH)
    {
        if(depth==MAXDEPTH)
        {
            best_score = 0;
        }



        return make_pair(best_score, best_move);
    }

    vector< pair<int, int>> legal_moves = possibleMoves(tigersTurn);



    for (int i = 0; i < legal_moves.size(); i++)
    {
        pair<int, int> curr_move = legal_moves[i];
        char marker;
        int bonus = 0 ;
        int val = -1;
        int index_of_goat = -1;
        if(tigersTurn)
        {
            marker = 'T';
            int val1, val2;

            if(isCaptured(curr_move.first,curr_move.second,&val)) //this is the capture move
            {
                bonus = 1000;
                val1 = curr_move.first;
                val2 = curr_move.second;
                grid[mp2[val1].first][mp2[val1].second] = '*';
                grid[mp2[val2].first][mp2[val2].second] = 'T';
                grid[mp2[val].first][mp2[val].second] = '*';
                swap(node_to_tiger[val1],node_to_tiger[val2]);
                Tiger[node_to_tiger[val2]]=val2;
                index_of_goat = node_to_goat[val];
                GOAT[node_to_goat[val]]=-1;
                node_to_goat[val]=-1;
                numOfGoat--;


            }
            else
            {
                val1 = curr_move.first;
                val2 = curr_move.second;
                grid[mp2[val1].first][mp2[val1].second] = '*';
                grid[mp2[val2].first][mp2[val2].second] = 'T';
                swap(node_to_tiger[val1],node_to_tiger[val2]);
                Tiger[node_to_tiger[val2]]=val2;
            }
        }
        else
        {
            int val1 = curr_move.first;
            int val2 = curr_move.second;
            grid[mp2[val1].first][mp2[val1].second] = '*';
            grid[mp2[val2].first][mp2[val2].second] = 'G';
            swap(node_to_goat[val1],node_to_goat[val2]);
            GOAT[node_to_goat[val2]]=val2;


        }



        // Maximizing player's turn
        if (tigersTurn)
        {
            pair<int,pair<int,int> > p  = minimax_optimization(false, depth + 1, alpha, beta);

            int score = p.first;

            if(val==-1)
            {
                grid[mp2[curr_move.first].first][mp2[curr_move.first].second] = 'T';
                grid[mp2[curr_move.second].first][mp2[curr_move.second].second] = '*';
                int val1 = curr_move.second;
                int val2 = curr_move.first;
                swap(node_to_tiger[val1],node_to_tiger[val2]);
                Tiger[node_to_tiger[val2]]=val2;


            }
            else
            {


                int val1 = curr_move.first;
                int val2 = curr_move.second;
                grid[mp2[val1].first][mp2[val1].second] = 'T';
                grid[mp2[val2].first][mp2[val2].second] = '*';
                grid[mp2[val].first][mp2[val].second] = 'G';

                swap(node_to_tiger[val2],node_to_tiger[val1]);
                Tiger[node_to_tiger[val1]]=val1;


                GOAT[index_of_goat]=val;
                node_to_goat[val]=index_of_goat;
                numOfGoat++;

            }

            if (best_score < score)
            {
                best_score = score - depth * 10 + bonus;
                best_move = curr_move;
                alpha = max(alpha, best_score);

                if (beta <= alpha)
                {
                    break;
                }
            }

        }
        else
        {
            pair<int,pair<int,int> > p = minimax_optimization(true, depth + 1, alpha, beta);
            int score = p.first;
            beta = min(beta, best_score);
            int val2 = curr_move.first;
            int val1 = curr_move.second;
            grid[mp2[val1].first][mp2[val1].second] = '*';
            grid[mp2[val2].first][mp2[val2].second] = 'G';
            swap(node_to_goat[val1],node_to_goat[val2]);
            GOAT[node_to_goat[val2]]=val2;

            if (best_score > score)
            {
                best_score = score + depth * 10;
                best_move = curr_move;

                if (beta <= alpha)
                {
                    break;
                }
            }
        }
    }

    return make_pair(best_score, best_move);
}





void displayBoard()
{
    printf("\nInitial grid:                   cell representation: \n");
    show_grid();
}



void goatMove(bool tigerIsAI)
{
    int val1,val2;
    char c1,c2;
    while(true)
    {


        if(!isThereAnyPossibleMoveExistsForGoat())
        {
            printf("\nGame Over!!! AI with Tiger won!!\n");
        }
        if(!tigerIsAI)
        {
            printf("\AI with Goat: \n");
            pair<int,int> p  = minimax_optimization(tigerIsAI,0,GOATWIN,TIGERWIN).second;
            val1 = p.first;
            val2 = p.second;
            cout<<"From cell: "<<(char)(val1+'A')<<" To cell: "<<(char)(val2+'A')<<endl;

        }
        else
        {
            printf("\nPlayer with Goat: \n");
            printf("From cell: ");

            cin>>c1;
            if(c1>='A' && c1<='Y')
                val1 = (int)c1-'A';
            else
                cout<<"\nInvalid input!!!\n";
            if(node_to_goat[val1]==-1)
            {
                printf("\nNo goat in this cell\n");
                continue;
            }
            printf("To cell: ");
            cin>>c2;
            if(c2>='A' && c2<='Y')
            {
                val2 = (int)c2-'A';
            }

            else
            {
                cout<<"\nInvalid input!!!\n";
                continue;
            }
        }



        if(isTheCellEmpty(val2))
        {
            if(isTheMoveValid(val1,val2))
            {
                grid[mp2[val1].first][mp2[val1].second] = '*';
                grid[mp2[val2].first][mp2[val2].second] = 'G';

                swap(node_to_goat[val1],node_to_goat[val2]);
                GOAT[node_to_goat[val2]]=val2;
                break;

            }
            else
            {

                printf("\nInvalid move!!! Goat can't  move from %c to %c\n",c1,c2);
                continue;
            }
        }
        else
        {
            printf("\n The cell you choose to move the goat, is not empty \n");
            ///i = i+9;
            continue;
        }
    }

}

void tigerMove(bool tigerIsAI )
{

    while(true)
    {
        int val1, val2;

        if(!isThereAnyPossibleMoveExistsForTiger())
        {
            printf("\n Game over!! Player with Goat won!!!\n");
            break;
        }

        if(tigerIsAI)
        {
            printf("\AI with Tiger: \n");
            pair<int,int> p  = minimax_optimization(tigerIsAI,0,GOATWIN,TIGERWIN).second;
            val1 = p.first;
            val2 = p.second;
            cout<<"From cell: "<<(char)(val1+'A')<<" To cell: "<<(char)(val2+'A')<<endl;
        }
        else
        {
            cout <<"Player with tiger\n\n";
            char c1,c2;
            printf("From cell: ");
            cin>>c1;
            if(c1>='A' && c1<='Y')
            {
                val1 = (int)c1-'A';
            }

            else
            {
                cout<<"\nInvalid input!!!\n";
                continue;
            }

            if(node_to_tiger[val1]==-1)
            {
                printf("\nNo Tiger in this cell\n");
                //i=i+9;
                continue;
            }
            printf("To cell: ");
            cin>>c2;
            if(c2>='A' && c2<='Y')
            {
                val2 = (int)c2-'A';
            }

            else
            {
                cout<<"\nInvalid input!!!\n";
                continue;
            }

        }

        if(isTheCellEmpty(val2))
        {
            if(isTheMoveValid(val1,val2))
            {
                grid[mp2[val1].first][mp2[val1].second] = '*';
                grid[mp2[val2].first][mp2[val2].second] = 'T';
                swap(node_to_tiger[val1],node_to_tiger[val2]);
                Tiger[node_to_tiger[val2]]=val2;
                break;

            }
            else
            {
                int val=-1;
                if(isCaptured(val1,val2,&val))
                {
                    grid[mp2[val1].first][mp2[val1].second] = '*';
                    grid[mp2[val2].first][mp2[val2].second] = 'T';
                    grid[mp2[val].first][mp2[val].second] = '*';
                    swap(node_to_tiger[val1],node_to_tiger[val2]);
                    Tiger[node_to_tiger[val2]]=val2;
                    cout <<"                Goat at "<<(char)(val+'A')<<" is captured!!!\n";
                    GOAT[node_to_goat[val]]=-1;
                    node_to_goat[val]=-1;
                    numOfGoat--;
                    if(numOfGoat<16)
                    {
                        printf("\nGame over!!! Player with tiger Win!!!\n");
                        break;
                    }
                    break;

                }
                else
                {

                    printf("\nInvalid move!!! Tiger can't  move from %c to %c\n",val1+'A',val2+'A');
                    continue;
                }
            }
        }
        else
        {
            printf("\n The cell you choose to move the tiger, is not empty \n");
            continue;
        }


    }
}



int main()
{
    string x;
    bool isTigerAI = false;
    while(true)
    {
        cout<<"To play with Goat press 1\nTo play with Tiger press 0\nInput: ";
        cin >> x;
        if(x.size() == 1 && x[0] == '1')
        {
            isTigerAI = true;
            break;
        }
        else if(x.size() == 1 && x[0] == '0')
        {
            isTigerAI = false;
            break;
        }
        else
        {
            cout <<"Invalid input!!! Please try again"<<endl;
        }
    }

    int i=1;
    initiateEverything();
    displayBoard();

    while(true)
    {
        cout <<"                     Round "<<i++<<endl;
        tigerMove(isTigerAI);
        displayBoard();
        goatMove(isTigerAI);
        displayBoard();
        if(!isThereAnyPossibleMoveExistsForGoat() || numOfGoat<16)
        {
            cout <<"########### TIGER WINS!!! ###########"<<endl;
            break;
        }
        else if(!isThereAnyPossibleMoveExistsForTiger())
        {
            cout <<"########### GOAT WINS!!! ###########"<<endl;
            break;
        }

    }
    cout<< "\n\n\n################ Thanks for Playing ###################\n";



}
