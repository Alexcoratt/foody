CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    name VARCHAR(64) UNIQUE NOT NULL,
    bio TEXT
);

CREATE TABLE products (
    id SERIAL PRIMARY KEY,
    name VARCHAR(256) NOT NULL,
    description TEXT,
    creator INTEGER REFERENCES users(id) ON DELETE CASCADE
);

CREATE TABLE nutricional_values (
    id INTEGER PRIMARY KEY REFERENCES products(id) ON DELETE CASCADE,
    prot REAL DEFAULT 0,
    fat REAL DEFAULT 0,
    carb REAL DEFAULT 0,
    cal REAL DEFAULT 0
);

CREATE TABLE recipes (
    id SERIAL PRIMARY KEY,
    name VARCHAR(256) NOT NULL,
    description TEXT,
    creator INTEGER REFERENCES users(id)
);

CREATE TABLE recipe_product_rels (
    recipe INTEGER PRIMARY KEY REFERENCES recipes(id) ON DELETE CASCADE,
    product INTEGER PRIMARY KEY REFERENCES products(id) ON DELETE RESTRICT,
    amount REAL DEFAULT 0
);

CREATE TABLE nested_recipes (
    aggregate INTEGER PRIMARY KEY REFERENCES recipes(id) ON DELETE CASCADE,
    component INTEGER PRIMARY KEY REFERENCES recipes(id) ON DELETE RESTRICT,
    amount REAL DEFAULT 0
);
