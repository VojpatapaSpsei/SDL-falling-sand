#include "Map.hpp"
#include "game.hpp"

Map::Map(int width, int height, int Cwidth)
{
    srand(time(NULL));

    wi=width/Cwidth;
    he=height/Cwidth;
    Cwi=Cwidth;

    dst.w=Cwidth;
    dst.h=Cwidth;

    mx=width/2;
    my=height/2;



    map = (struct tile**) malloc(he * sizeof(struct tile**));
    for (i = 0; i < he; i++)
    {
        map[i] = (struct tile*) malloc(wi * sizeof(struct tile*));
    }



    src.x=0;
    src.y=0;
    src.h=Cwidth;
    src.w=Cwidth;

    for(i=0;i<he;i++)
    {
        for(j=0;j<wi;j++)
        {
                map[i][j].Material=0;
                map[i][j].Selected=0;
        }
    }

    sand=TextureManager::TextureLoader("images/sand.png");
    selected=TextureManager::TextureLoader("images/selected.png");
}

Map::~Map()
{

}

void Map::Update()
{
    Mouse();

    Physics();

}

void Map::Render()
{
    for(i=0;i<he;i++)
    {
        for(j=0;j<wi;j++)
        {
            if(map[i][j].Material==1)
            {
                dst.x=Cwi*j;
                dst.y=Cwi*i;

                SDL_RenderCopy(Game::renderer,sand,&src,&dst);

            }
            if(map[i][j].Selected==1)
            {
                dst.x=Cwi*j;
                dst.y=Cwi*i;

                SDL_RenderCopy(Game::renderer,selected,&src,&dst);
            }
        }
    }
}

void Map::Physics()
{
    for(i=he-1;i>=0;i--)
    {
        for(j=0;j<wi;j++)
        {
            bool Down=(i+1<=he-1 && map[i+1][j].Material==0);
            bool DownLeft=(i+1<=he-1 && j-1>=0 && map[i][j-1].Material!=1 && map[i+1][j-1].Material==0);
            bool DownRight=(i+1<=he-1 && j+1<=wi-1 && map[i][j+1].Material!=1 && map[i+1][j+1].Material==0);

            if(map[i][j].Material==1)
            {
                if(Down)
                {
                    temp=map[i][j].Material;
                    map[i][j].Material=map[i+1][j].Material;
                    map[i+1][j].Material=temp;
                }
                else if(DownLeft && DownRight)
                {
                    k=rand()%(2-1+1)+1;

                    if(k==2)
                    {
                        temp=map[i][j].Material;
                        map[i][j].Material=map[i+1][j+1].Material;
                        map[i+1][j+1].Material=temp;
                    }
                    else
                    {
                        temp=map[i][j].Material;
                        map[i][j].Material=map[i+1][j-1].Material;
                        map[i+1][j-1].Material=temp;
                    }
                }
                else if(DownLeft)
                {
                    temp=map[i][j].Material;
                    map[i][j].Material=map[i+1][j-1].Material;
                    map[i+1][j-1].Material=temp;
                }
                else if(DownRight)
                {
                    temp=map[i][j].Material;
                    map[i][j].Material=map[i+1][j+1].Material;
                    map[i+1][j+1].Material=temp;
                }
            }
        }
    }
}

void Map::Mouse()
{

Uint32 mouse = SDL_GetMouseState(&mx,&my);

mx/=Cwi;
my/=Cwi;

    if(Game::ScrollUp)
    {
        brushsize=brushsize+2.5;
    }
    if(Game::ScrollDown)
    {
        brushsize=brushsize-2.5;
    }
    if(brushsize<2.0)
    {
        brushsize=2.0;
    }
    if(brushsize>25.0)
    {
        brushsize=25.0;
    }

        for (i = 0; i < he; i++)
        {
            for ( j = 0; j < wi; j++)
            {
                int dx = j - mx;
                int dy = i - my;
                float distance = sqrt(dx * dx + dy * dy);

                if (distance < brushsize)
                {
                        map[i][j].Selected = 1;
                }
                else
                {
                    map[i][j].Selected = 0;
                }

            }
        }

    if(Game::LeftClick)
    {
        for(i=0;i<he;i++)
        {
            for(j=0;j<wi;j++)
            {
                if(map[i][j].Selected==1)
                {
                        map[i][j].Material=1;
                }
            }
        }
    }

    if(Game::RightClick)
    {
        for(i=0;i<he;i++)
        {
            for(j=0;j<wi;j++)
            {
                if(map[i][j].Selected==1)
                {
                    map[i][j].Material=0;
                }
            }
        }
    }
}


