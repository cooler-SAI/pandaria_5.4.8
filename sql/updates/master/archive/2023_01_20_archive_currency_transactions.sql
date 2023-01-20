/*
 Navicat Premium Data Transfer

 Source Server         : 1
 Source Server Type    : MySQL
 Source Server Version : 80031
 Source Host           : localhost:3306
 Source Schema         : archive

 Target Server Type    : MySQL
 Target Server Version : 80031
 File Encoding         : 65001

 Date: 20/01/2023 11:05:48
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for currency_transactions
-- ----------------------------
DROP TABLE IF EXISTS `currency_transactions`;
CREATE TABLE `currency_transactions`  (
  `realmid` tinyint UNSIGNED NOT NULL DEFAULT 1,
  `id` int UNSIGNED NOT NULL AUTO_INCREMENT,
  `guid` int UNSIGNED NOT NULL,
  `unix_time` int UNSIGNED NOT NULL,
  `operation` enum('LOOT_MOB','LOOT_ITEM','MAIL','QUEST_REWARD','TRADE','SELL_ITEM','GUILD_BANK','AUCTION','TRANSMOGRIFICATION') CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `param` int UNSIGNED NULL DEFAULT NULL,
  `attachments` text CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `amount_before` bigint UNSIGNED NULL DEFAULT NULL,
  `amount_after` bigint UNSIGNED NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `idx_guid`(`guid`) USING BTREE,
  INDEX `idx_operation`(`operation`) USING BTREE,
  INDEX `idx_unix_time`(`unix_time`) USING BTREE,
  INDEX `idx_param`(`param`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 2361 CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
