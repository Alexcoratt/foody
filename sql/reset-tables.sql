DROP TABLE IF EXISTS users CASCADE;
CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    login VARCHAR(128) UNIQUE NOT NULL,
    bio TEXT
);

DROP TABLE IF EXISTS products CASCADE;
CREATE TABLE products (
    id SERIAL PRIMARY KEY,
    name VARCHAR(256) NOT NULL,
    notes TEXT,
    owner_id INTEGER NOT NULL REFERENCES users(id) ON DELETE RESTRICT,

    proteins REAL DEFAULT 0,
    fats REAL DEFAULT 0,
    carbohydrates REAL DEFAULT 0,
    calories REAL DEFAULT 0
);

DROP TABLE IF EXISTS recipes CASCADE;
CREATE TABLE recipes (
    id SERIAL PRIMARY KEY,
    name VARCHAR(256) NOT NULL,
    notes TEXT,
    owner_id INTEGER NOT NULL REFERENCES users(id) ON DELETE RESTRICT
);

DROP TABLE IF EXISTS recipe_products;
CREATE TABLE recipe_products (
    recipe_id INTEGER REFERENCES recipes(id) ON DELETE CASCADE,
    product_id INTEGER REFERENCES products(id) ON DELETE RESTRICT,
    amount REAL DEFAULT 0,

    PRIMARY KEY(recipe_id, product_id)
);

DROP TABLE IF EXISTS nested_recipes;
CREATE TABLE nested_recipes (
    aggregate_id INTEGER REFERENCES recipes(id) ON DELETE CASCADE,
    component_id INTEGER REFERENCES recipes(id) ON DELETE RESTRICT,
    amount REAL DEFAULT 0,

    PRIMARY KEY(aggregate_id, component_id)
);
