#import <Athena/GameStates/IGameState.h>


class MainGameState: public Athena::GameStates::IGameState
{
        //_____ Construction / Destruction __________
public:
    MainGameState();
    virtual ~MainGameState();


    //_____ Methods to be overriden by each state __________
public:
    virtual void enter();
    virtual void exit();
    virtual void pause();
    virtual void resume();

    virtual void process();


    //_____ Attributes __________
private:
    Athena::Entities::Scene*    m_pScene;
    Athena::Entities::Entity*   m_pCameraEntity;
    Athena::Entities::Entity*   m_pEntity;
};
