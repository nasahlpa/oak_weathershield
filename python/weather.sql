-- phpMyAdmin SQL Dump
-- version 4.5.5.1deb2
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Erstellungszeit: 23. Mrz 2016 um 14:42
-- Server-Version: 5.6.28-1
-- PHP-Version: 5.6.17-3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

CREATE TABLE `weather` (
  `date` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `temperature` float DEFAULT NULL,
  `ambient` int(8) DEFAULT NULL,
  `pressure` float DEFAULT NULL,
  `humidity` float DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

