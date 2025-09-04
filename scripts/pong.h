//
// Created by henry on 9/2/25.
//

#ifndef HGAMETEMPLATE_PONG_H
#define HGAMETEMPLATE_PONG_H

#include <hagame/core/script.h>

class Pong : public hg::Script {
public:
    Pong(hg::Scene* scene): hg::Script(scene) {}

protected:

    void onUpdate(double dt) override;

    hg::ScriptDef getDef() const override;
};

HG_SCRIPT(Pong)

#endif //HGAMETEMPLATE_PONG_H
