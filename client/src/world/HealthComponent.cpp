//
// Created by cedric on 2022-10-01.
//

#include "HealthComponent.h"

template <typename T>
void HealthComponent<T>::heal(T amount) {
    health += amount;

    if(health > maxHealth)
        health = maxHealth;
}

template<typename T>
void HealthComponent<T>::damage(T amount) {
    health -= amount;

    if(health < static_cast<T>(0.0))
        health = static_cast<T>(0.0);
}

template<typename T>
T HealthComponent<T>::get_health() const {
    return health;
}

template <typename T>
bool HealthComponent<T>::is_dead() const {
    return health <= static_cast<T>(0.0);
}