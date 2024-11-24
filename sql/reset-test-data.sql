TRUNCATE TABLE users CASCADE;
ALTER SEQUENCE users_id_seq RESTART WITH 1;
INSERT INTO users (login, bio)
VALUES
    ('alexsm', 'Just a creator'),
    ('unknown', 'Who is that?'),
    ('test-user', 'User for tests'),
    ('test-user2', 'Friend of test-user')
;

TRUNCATE TABLE products CASCADE;
ALTER SEQUENCE products_id_seq RESTART WITH 1;
INSERT INTO products (name, notes, owner_id, proteins, fats, carbohydrates, calories)
VALUES
    ('Чудо творожок 2 слоя персик-груша', 'Десерт творожный', 1, 4.3, 4.2, 19.7, 134),
    ('Помидорка томатная паста', 'Лучшая томатная паста на свете', 1, 5, 0.5, 16, 90),
    ('Простоквашино молоко пастеризованное 1.5%', '', 2, 2.9, 1.5, 4.9, 188)
;

TRUNCATE TABLE recipes CASCADE;
ALTER SEQUENCE recipes_id_seq RESTART WITH 1;
INSERT INTO recipes (name, notes, owner_id)
VALUES
    ('Томатное молоко', 'Это страшно', 1),
    ('Томатный чудо творожок', 'Это звучит еще страшнее', 1),
    ('Чудо творожок с молоком', 'Адекватно', 2),
    ('Опасный замес', '...', 1)
;

TRUNCATE TABLE recipe_products;
INSERT INTO recipe_products (recipe_id, product_id, amount)
VALUES
    (1, 3, 0.5),
    (1, 2, 0.2),

    (2, 1, 0.2),
    (2, 2, 0.05),

    (3, 1, 0.2),
    (3, 3, 0.4),

    (4, 1, 0.2)
;

TRUNCATE TABLE nested_recipes;
INSERT INTO nested_recipes (aggregate_id, component_id, amount)
VALUES
    (4, 3, 0.5)
;