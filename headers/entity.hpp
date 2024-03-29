#ifndef SPUTIFY_ENTITY_HPP
#define SPUTIFY_ENTITY_HPP

class Entity {
private:
    bool deleted = false;

public:
    bool isDeleted() const;
    
    void markAsDeleted();
};

#endif