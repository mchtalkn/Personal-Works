#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>
using namespace std;
const int N=11;
const int BLUE = 1;
const int RED = 2;

typedef class Hex
{
    vector<int> g[N*N];
    int mat[N][N];
    int mc, uc;

    public:

    Hex(int a): uc(a),mc(3-a)
    {
        for(int i=0; i<N;++i)
        {
            for(int j=0; j<N; ++j)
            {
                mat[i][j]=0;
            }
        }
    }
     void addEdge(int i, int j, int c)
    {
        int row;
        int row1 = (i*N+j);
                if(((i==0)&&(j==0)) || ((i==N-1)&&(j==N-1)))
                {
                    if(mat[i][j+1]==c)
                    {
                        row=(i*N+j+1);
                        g[i*N+j].push_back(row);
                        g[i*N+j+1].push_back(row1);
                    }

                    if(mat[(i+1)][j]==c)
                    {
                        row=((i+1)*N+j);
                        g[i*N+j].push_back(row);
                        g[(i+1)*N+j].push_back(row1);
                    }
                }
                else if(((i==0)&&(j==N-1)) || ((i==N-1)&&(j==0)))
                {
                    if(i==0)
                    {
                        if(mat[i][j-1]==c)
                        {
                            row=(i*N+j-1);
                            g[i*N+j].push_back(row);
                            g[i*N+j-1].push_back(row1);
                        }

                        if(mat[(i+1)][j]==c)
                        {
                            row=((i+1)*N+j);
                            g[i*N+j].push_back(row);
                            g[(i+1)*N+j].push_back(row1);
                        }

                        if(mat[(i+1)][j-1]==c)
                        {
                            row=((i+1)*N+j-1);
                            g[i*N+j].push_back(row);
                            g[(i+1)*N+j-1].push_back(row1);
                        }
                    }
                    else
                    {
                        if(mat[i][j+1]==c)
                        {
                            row=(i*N+j+1);
                            g[i*N+j].push_back(row);
                            g[i*N+j+1].push_back(row1);
                        }

                        if(mat[(i-1)][j]==c)
                        {
                            row=((i-1)*N+j);
                            g[i*N+j].push_back(row);
                            g[(i-1)*N+j].push_back(row1);
                        }

                        if(mat[(i-1)][j+1]==c)
                        {
                            row=((i-1)*N+j+1);
                            g[i*N+j].push_back(row);
                            g[(i-1)*N+j+1].push_back(row1);
                        }
                    }
                }
                else if(i==0)
                {
                    if(mat[i][j-1]==c)
                    {
                        row=(i*N+j-1);
                        g[i*N+j].push_back(row);
                        g[i*N+j-1].push_back(row1);
                    }

                    if(mat[i][j+1]==c)
                    {
                        row=(i*N+j+1);
                        g[i*N+j].push_back(row);
                        g[i*N+j+1].push_back(row1);
                    }

                    if(mat[(i+1)][j]==c)
                    {
                        row=((i+1)*N+j);
                        g[i*N+j].push_back(row);
                        g[(i+1)*N+j].push_back(row1);
                    }

                    if(mat[(i+1)][j-1]==c)
                    {
                        row=((i-1)*N+j-1);
                        g[i*N+j].push_back(row);
                        g[(i+1)*N+j-1].push_back(row1);
                    }
                }
                else if(i==N-1)
                {
                    if(mat[i][j-1]==c)
                    {
                        row=(i*N+j-1);
                        g[i*N+j].push_back(row);
                        g[i*N+j-1].push_back(row1);
                    }

                    if(mat[i][j+1]==c)
                    {
                        row=(i*N+j+1);
                        g[i*N+j].push_back(row);
                        g[i*N+j+1].push_back(row1);
                    }

                    if(mat[(i-1)][j]==c)
                    {
                        row=((i-1)*N+j);
                        g[i*N+j].push_back(row);
                        g[(i-1)*N+j].push_back(row1);
                    }

                    if(mat[(i-1)][j-1]==c)
                    {
                        row=((i-1)*N+j-1);
                        g[i*N+j].push_back(row);
                        g[(i-1)*N+j-1].push_back(row1);
                    }
                }
                else if(j==0)
                {
                    if(mat[(i+1)][j]==c)
                    {
                        row=((i+1)*N+j);
                        g[i*N+j].push_back(row);
                        g[(i+1)*N+j].push_back(row1);
                    }

                    if(mat[i][j+1]==c)
                    {
                        row=((i)*N+j+1);
                        g[i*N+j].push_back(row);
                        g[i*N+j+1].push_back(row1);
                    }

                    if(mat[(i-1)][j]==c)
                    {
                        row=((i-1)*N+j);
                        g[i*N+j].push_back(row);
                        g[(i-1)*N+j].push_back(row1);
                    }

                    if(mat[(i-1)][j-1]==c)
                    {
                        row=((i-1)*N+j-1);
                        g[i*N+j].push_back(row);
                        g[(i-1)*N+j-1].push_back(row1);
                    }
                }
                else if(j==N-1)
                {
                    if(mat[i][j-1]==c)
                    {
                        row=((i)*N+j-1);
                        g[i*N+j].push_back(row);
                        g[i*N+j-1].push_back(row1);
                    }

                    if(mat[(i-1)][j]==c)
                    {
                        row=((i-1)*N+j);
                        g[i*N+j].push_back(row);
                        g[(i-1)*N+j].push_back(row1);
                    }

                    if(mat[(i+1)][j]==c)
                    {
                        row=((i+1)*N+j);
                        g[i*N+j].push_back(row);
                        g[(i+1)*N+j].push_back(row1);
                    }

                    if(mat[(i+1)][j-1]==c)
                    {
                        row=((i+1)*N+j-1);
                        g[i*N+j].push_back(row);
                        g[(i+1)*N+j-1].push_back(row1);
                    }
                }
                else
                {
                    if(mat[i][j-1]==c)
                    {
                        row=((i)*N+j-1);
                        g[i*N+j].push_back(row);
                        g[i*N+j-1].push_back(row1);
                    }

                    if(mat[i][j+1]==c)
                    {
                        row=((i)*N+j+1);
                        g[i*N+j].push_back(row);
                        g[i*N+j+1].push_back(row1);
                    }

                    if(mat[(i-1)][j]==c)
                    {
                        row=((i-1)*N+j);
                        g[i*N+j].push_back(row);
                        g[(i-1)*N+j].push_back(row1);
                    }

                    if(mat[(i-1)][j+1]==c)
                    {
                        row=((i-1)*N+j+1);
                        g[i*N+j].push_back(row);
                        g[(i-1)*N+j+1].push_back(row1);
                    }

                    if(mat[(i+1)][j]==c)
                    {
                        row=((i+1)*N+j);
                        g[i*N+j].push_back(row);
                        g[(i+1)*N+j].push_back(row1);
                    }

                    if(mat[(i+1)][j-1]==c)
                    {
                        row=((i+1)*N+j-1);
                        g[i*N+j].push_back(row);
                        g[(i+1)*N+j-1].push_back(row1);
                    }
                }
    }

    void display()
    {
        for(int i=0; i<N; ++i)
        {
            for(int j=0; j<N; ++j)
            {
                if(mat[i][j]==0)
                cout<<".    ";
                else if(mat[i][j]==BLUE)
                cout<<"B    ";
                else
                cout<<"R    ";
            }
            cout<<endl;
        }
    }

    int bfsv1(int i, int j, int c)
    {
        int maxi=0;
        queue<int> q;
        q.push(i*N+j);
        int size =1 ;
        bool vis[121]={false,};
        vis[i*N+j]=true;
        while(size)
        {
            int size1 = size;
            for(int z=0; z<size1; ++z)
            {
                int x = q.front();
                q.pop();
                --size;

                int size2 = g[x].size();

                for(int y=0; y<size2;++y)
                {
                    int a = g[x][y];
                    if(vis[a]==true)
                    continue;
                    if(a/N > x/N)
                    {
                        q.push(a);
                        ++size;
                        vis[a]=true;
                    }
                }

            }
            if(size)
            ++maxi;
        }
        return maxi;
    }

    int bfsh1(int i, int j, int c)
    {
        int maxi=0;
        queue<int> q;
        q.push(i*N+j);
        int size =1 ;
        bool vis[121]={false,};
        vis[i*N+j]=true;
        while(size)
        {
            int size1 = size;
            for(int z=0; z<size1; ++z)
            {
                int x = q.front();
                q.pop();
                --size;

                int size2 = g[x].size();

                for(int y=0; y<size2;++y)
                {
                    int a = g[x][y];
                    if(vis[a]==true)
                    continue;
                    if(a%N > x%N)
                    {
                        q.push(a);
                        ++size;
                        vis[a]=true;
                    }
                }

            }
            if(size)
            ++maxi;
        }
        return maxi;
    }

    int bfsv(int c)
    {
        int maxi =0;
        for(int i=0; i<N; ++i)
        {
            if(mat[0][i]==c)
            {
                int ret = bfsv1(0,i,c);
                if(ret >maxi)
                maxi = ret;
            }
        }
        return maxi;
    }

    int bfsh(int c)
    {
        int maxi =0;
        for(int i=0; i<N; ++i)
        {
            if(mat[i][0]==c)
            {
                int ret = bfsh1(i,0,c);
                if(ret >maxi)
                maxi = ret;
            }
        }
        return maxi;
    }

     int play(int i, int j, int c)
    {
        int maxi;

            if(mat[i][j]==0)
            {
                mat[i][j]=uc;

                addEdge(i,j,uc);

                if(uc==BLUE)
                {
                    maxi = bfsh(uc);
                    if(maxi==N-1)
                    {
                        cout<<"You won"<<endl;
                        return 1;
                    }
                }
                else
                {
                    maxi = bfsv(uc);
                    if(maxi == N-1)
                    {
                        cout<<"You won"<<endl;
                        return 1;
                    }
                }

                    while(1)
                    {
                       i = rand()%N;
                        j = rand()%N;

                        if(mat[i][j]==0)
                        {
                            mat[i][j]=mc;
                            break;
                        }
                    }
                    addEdge(i,j,mc);

                    if(mc==BLUE)
                    {
                        maxi = bfsh(mc);
                        if(maxi == N-1)
                        {
                            cout<<"I won"<<endl;
                            return 1;
                        }
                    }
                    else
                    {
                        maxi = bfsv(mc);
                        if(maxi == N-1)
                        {
                            cout<<"I won"<<endl;
                            return 1;
                        }
                    }
            }
            else
            {
                cout<<"Invalid choice"<<endl;
            }

        return 0;
    }

}Hex;


int main()
{
    srand(time(NULL));
    cout<<"Enter your color 1 for blue or 2 for red"<<endl;
    int col,ret;
    char ch;
    cin>>col;
    Hex h(col);

    cout<<"Enter p <x co-ordinate> <y co-ordinate> to play"<<endl;
    cout<<"Enter d for display of board"<<endl;
	cout<<"Enter q to quit"<<endl;

    while(1)
    {
	cout<<"Enter :"<<endl;
        cin>>ch;
        if(ch=='p')
        {
            int i,j;
            cin>>i>>j;
			if((i>=0)&&(i<N)&&(j>=0)&&(j<N))
			{
				ret = h.play(i,j,col);
				if(ret)
				break;
			}
        }
        else if(ch=='d')
        {
            h.display();
        }
		else if(ch == 'q')
		{
			cout<<"Its a draw"<<endl;
			break;
		}
        else
        {
            cout<<"Invalid option"<<endl;
        }
    }
    h.display();
return 0;

}
