#ifndef ESPMANAGER_H
#define ESPMANAGER_H

#include <jni.h>

struct enemy_t {
    void *object;
};

class ESPManager {
public:

    void* MyPlayer = NULL;

    std::vector<enemy_t *> *enemies;
	
    ESPManager() {
        enemies = new std::vector<enemy_t *>();
    }
	
    bool isEnemyPresent(void *enemyObject) {
        for (std::vector<enemy_t *>::iterator it = enemies->begin(); it != enemies->end(); it++) {
            if ((*it)->object == enemyObject) {
                return true;
            }
        }
        return false;
    }
    void removeEnemy(enemy_t *enemy) {
        for (int i = 0; i < enemies->size(); i++) {
            if ((*enemies)[i] == enemy) {
                enemies->erase(enemies->begin() + i);
                return;
            }
        }
    }
    void tryAddEnemy(void *enemyObject) {
        if (isEnemyPresent(enemyObject)) {
            return;
        }
        enemy_t *newEnemy = new enemy_t();

        newEnemy->object = enemyObject;
		
        enemies->push_back(newEnemy);
    }
	
	void tryAddMyPlayer(void *enemyObject) {
		if (MyPlayer==NULL)
		    MyPlayer = enemyObject;
    }
    
    void removeEnemyGivenObject(void *enemyObject) {
        for (int i = 0; i < enemies->size(); i++) {
            if ((*enemies)[i]->object == enemyObject) {
                enemies->erase(enemies->begin() + i);
                return;
            }
        }
    }
	
	void removeAllEnemyGivenObject() {
		MyPlayer = NULL;
        for (int i = 0; i < enemies->size(); i++) {
            enemies->erase(enemies->begin() + i);
        }
    }

};

#endif
