//
// Created by cedric on 2022-10-01.
//

#ifndef LD51_CLIENT_HEALTHCOMPONENT_H
#define LD51_CLIENT_HEALTHCOMPONENT_H

template<typename T>
class HealthComponent {
public:
    explicit HealthComponent(T maxHealth) : maxHealth(maxHealth), health(maxHealth) {}

    void heal(T amount);

    void damage(T amount);

    [[nodiscard]] T get_health() const;

    [[nodiscard]] bool is_dead() const;

protected:
    T maxHealth;
    T health;
};


template class HealthComponent<int>;
template class HealthComponent<float>;
#endif //LD51_CLIENT_HEALTHCOMPONENT_H
