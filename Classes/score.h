// Created by 冯天阳

#ifndef POBG_SCORE_H
#define POBG_SCORE_H


#include "score.h"

USING_NS_CC;

class score {
public:
    ~score() {
    }

    score(const score &) = delete;

    score &operator=(const score &) = delete;

    static score &getInstance() {
        static score instance;
        return instance;
    }

    int score = 0;

private:
    score() {
    }
};


#endif //POBG_SCORE_H
