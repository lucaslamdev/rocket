CREATE DATABASE DB_API;

--temperatura celcius
CREATE TABLE bmp (
    ID INT NOT NULL AUTO_INCREMENT,
    temperatura FLOAT NOT NULL,
    pressao FLOAT NOT NULL,
    altitude FLOAT NOT NULL,
    pressao_nivel_mar FLOAT NOT NULL,
    altitude_real FLOAT NOT NULL,
    data DATETIME NOT NULL,
    PRIMARY KEY (ID)
);

--ac = acelerometro - gy = Giroscopio - temperatura celsius
CREATE TABLE mpu (
    ID INT NOT NULL AUTO_INCREMENT,
    acX FLOAT NOT NULL,
    acY FLOAT NOT NULL,
    acZ FLOAT NOT NULL,
    gyX FLOAT NOT NULL,
    gyY FLOAT NOT NULL,
    gyZ FLOAT NOT NULL,
    temperatura FLOAT NOT NULL,
    velocIDade FLOAT NOT NULL,
    data DATETIME NOT NULL,
    PRIMARY KEY (ID)
);

--data_gps = data obtIDa do gps - data = data atual obtIDa pelo servIDor php
CREATE TABLE gps (
    ID INT NOT NULL AUTO_INCREMENT,
    qtd_satelites INT NOT NULL,
    latitude FLOAT NOT NULL,
    longitude FLOAT NOT NULL,
    altitude FLOAT NOT NULL,
    velocIDade FLOAT NOT NULL,
    data_gps DATETIME NOT NULL,
    data DATETIME NOT NULL,
    PRIMARY KEY (ID)
);