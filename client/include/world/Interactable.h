//
// Created by Winter on 02/10/2022.
//

#ifndef LD51_CLIENT_INTERACTABLE_H
#define LD51_CLIENT_INTERACTABLE_H


class Interactable {
public:
	virtual ~Interactable() = default;

	virtual void activate() = 0;
};


#endif //LD51_CLIENT_INTERACTABLE_H
