typedef struct term {
    float coef;
    int exp;
    struct term* link;
} term;

typedef struct {
    term* first;
    term* last;
} poly;

poly* create_poly();

void display_poly(poly* p);

void delete_poly(poly* p);

void insert_at_end(poly* p, float coef, int exp);

void insert_ord(poly* p, float coef, int exp);

poly* add_poly(poly* p1, poly* p2);

