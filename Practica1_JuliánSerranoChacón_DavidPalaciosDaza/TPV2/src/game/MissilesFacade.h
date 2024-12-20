#pragma once

class MissilesFacade
{
public:
    MissilesFacade() {
    }
    virtual ~MissilesFacade() {
    }
    virtual void create_missiles(int n) = 0;
    virtual void remove_all_missiles() = 0;
};