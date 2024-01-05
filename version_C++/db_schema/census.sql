DROP TABLE IF EXISTS vacensus;

CREATE TABLE vacensus(
    county TEXT,
    population INTEGER,
    group1 FLOAT(1), -- 0-15
    group2 FLOAT(1), -- 16-30
    group3 FLOAT(1), -- 31-45
    group4 FLOAT(1), -- 46-60
    group5 FLOAT(1)  -- 60+
);

SELECT * FROM vacensus;
