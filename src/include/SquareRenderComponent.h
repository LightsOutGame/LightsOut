//
// Created by Julian Reder on 6/13/25.
//

#pragma once



class SquareRenderComponent: public RenderComponent {
    public:
    SquareRenderComponent(EntityRef boundEntity, TylerDoesntLikeTheGameClass* game);
    KEYDEF(square)

    void onRender(TylerDoesntLikeTheGameClass& game);




};


