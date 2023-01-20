/*
 Navicat Premium Data Transfer

 Source Server         : 1
 Source Server Type    : MySQL
 Source Server Version : 80031
 Source Host           : localhost:3306
 Source Schema         : characters

 Target Server Type    : MySQL
 Target Server Version : 80031
 File Encoding         : 65001

 Date: 20/01/2023 08:58:46
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for pool_quest_save
-- ----------------------------
DROP TABLE IF EXISTS `pool_quest_save`;
CREATE TABLE `pool_quest_save`  (
  `pool_id` int UNSIGNED NOT NULL DEFAULT 0,
  `quest_id` int UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`pool_id`, `quest_id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of pool_quest_save
-- ----------------------------
INSERT INTO `pool_quest_save` VALUES (334, 30473);
INSERT INTO `pool_quest_save` VALUES (348, 24629);
INSERT INTO `pool_quest_save` VALUES (349, 14104);
INSERT INTO `pool_quest_save` VALUES (350, 13905);
INSERT INTO `pool_quest_save` VALUES (351, 13916);
INSERT INTO `pool_quest_save` VALUES (352, 11377);
INSERT INTO `pool_quest_save` VALUES (353, 11669);
INSERT INTO `pool_quest_save` VALUES (354, 13423);
INSERT INTO `pool_quest_save` VALUES (356, 11363);
INSERT INTO `pool_quest_save` VALUES (357, 11385);
INSERT INTO `pool_quest_save` VALUES (358, 14080);
INSERT INTO `pool_quest_save` VALUES (359, 14076);
INSERT INTO `pool_quest_save` VALUES (360, 14136);
INSERT INTO `pool_quest_save` VALUES (361, 14092);
INSERT INTO `pool_quest_save` VALUES (362, 12759);
INSERT INTO `pool_quest_save` VALUES (363, 14107);
INSERT INTO `pool_quest_save` VALUES (380, 12736);
INSERT INTO `pool_quest_save` VALUES (381, 12741);
INSERT INTO `pool_quest_save` VALUES (382, 12762);
INSERT INTO `pool_quest_save` VALUES (384, 13192);
INSERT INTO `pool_quest_save` VALUES (385, 13154);
INSERT INTO `pool_quest_save` VALUES (386, 12587);
INSERT INTO `pool_quest_save` VALUES (500, 13674);
INSERT INTO `pool_quest_save` VALUES (501, 13763);
INSERT INTO `pool_quest_save` VALUES (502, 13770);
INSERT INTO `pool_quest_save` VALUES (503, 13774);
INSERT INTO `pool_quest_save` VALUES (504, 13780);
INSERT INTO `pool_quest_save` VALUES (505, 13785);
INSERT INTO `pool_quest_save` VALUES (506, 13666);
INSERT INTO `pool_quest_save` VALUES (507, 13616);
INSERT INTO `pool_quest_save` VALUES (508, 13741);
INSERT INTO `pool_quest_save` VALUES (509, 13747);
INSERT INTO `pool_quest_save` VALUES (510, 13758);
INSERT INTO `pool_quest_save` VALUES (511, 13753);
INSERT INTO `pool_quest_save` VALUES (512, 13107);
INSERT INTO `pool_quest_save` VALUES (513, 13112);
INSERT INTO `pool_quest_save` VALUES (514, 13832);
INSERT INTO `pool_quest_save` VALUES (515, 12961);
INSERT INTO `pool_quest_save` VALUES (516, 24579);
INSERT INTO `pool_quest_save` VALUES (523, 14080);
INSERT INTO `pool_quest_save` VALUES (524, 14112);
INSERT INTO `pool_quest_save` VALUES (525, 14136);
INSERT INTO `pool_quest_save` VALUES (526, 14092);
INSERT INTO `pool_quest_save` VALUES (527, 14108);
INSERT INTO `pool_quest_save` VALUES (528, 26536);
INSERT INTO `pool_quest_save` VALUES (529, 29360);
INSERT INTO `pool_quest_save` VALUES (530, 29365);
INSERT INTO `pool_quest_save` VALUES (531, 29352);
INSERT INTO `pool_quest_save` VALUES (532, 29314);
INSERT INTO `pool_quest_save` VALUES (533, 29322);
INSERT INTO `pool_quest_save` VALUES (534, 29345);
INSERT INTO `pool_quest_save` VALUES (535, 29342);
INSERT INTO `pool_quest_save` VALUES (536, 29359);
INSERT INTO `pool_quest_save` VALUES (537, 30658);
INSERT INTO `pool_quest_save` VALUES (537, 30700);
INSERT INTO `pool_quest_save` VALUES (537, 30701);
INSERT INTO `pool_quest_save` VALUES (538, 31526);
INSERT INTO `pool_quest_save` VALUES (539, 32001);
INSERT INTO `pool_quest_save` VALUES (540, 26227);
INSERT INTO `pool_quest_save` VALUES (541, 26183);
INSERT INTO `pool_quest_save` VALUES (542, 26557);
INSERT INTO `pool_quest_save` VALUES (543, 25161);
INSERT INTO `pool_quest_save` VALUES (544, 25105);
INSERT INTO `pool_quest_save` VALUES (600, 31703);
INSERT INTO `pool_quest_save` VALUES (601, 30156);
INSERT INTO `pool_quest_save` VALUES (602, 31706);
INSERT INTO `pool_quest_save` VALUES (603, 31720);
INSERT INTO `pool_quest_save` VALUES (605, 31109);
INSERT INTO `pool_quest_save` VALUES (605, 31487);
INSERT INTO `pool_quest_save` VALUES (605, 31494);
INSERT INTO `pool_quest_save` VALUES (605, 31496);
INSERT INTO `pool_quest_save` VALUES (605, 31502);
INSERT INTO `pool_quest_save` VALUES (605, 31503);
INSERT INTO `pool_quest_save` VALUES (605, 31504);
INSERT INTO `pool_quest_save` VALUES (608, 31808);
INSERT INTO `pool_quest_save` VALUES (5662, 13675);
INSERT INTO `pool_quest_save` VALUES (5663, 13762);
INSERT INTO `pool_quest_save` VALUES (5664, 13769);
INSERT INTO `pool_quest_save` VALUES (5665, 13773);
INSERT INTO `pool_quest_save` VALUES (5666, 13778);
INSERT INTO `pool_quest_save` VALUES (5667, 13784);
INSERT INTO `pool_quest_save` VALUES (5668, 13670);
INSERT INTO `pool_quest_save` VALUES (5669, 13603);
INSERT INTO `pool_quest_save` VALUES (5670, 13741);
INSERT INTO `pool_quest_save` VALUES (5671, 13746);
INSERT INTO `pool_quest_save` VALUES (5672, 13759);
INSERT INTO `pool_quest_save` VALUES (5673, 13752);
INSERT INTO `pool_quest_save` VALUES (5674, 13107);
INSERT INTO `pool_quest_save` VALUES (5675, 13114);
INSERT INTO `pool_quest_save` VALUES (5676, 13832);
INSERT INTO `pool_quest_save` VALUES (5677, 12961);
INSERT INTO `pool_quest_save` VALUES (5678, 24581);
INSERT INTO `pool_quest_save` VALUES (30136, 32215);
INSERT INTO `pool_quest_save` VALUES (30136, 32217);
INSERT INTO `pool_quest_save` VALUES (30136, 32227);
INSERT INTO `pool_quest_save` VALUES (30136, 32729);
INSERT INTO `pool_quest_save` VALUES (30137, 32538);
INSERT INTO `pool_quest_save` VALUES (30137, 32540);
INSERT INTO `pool_quest_save` VALUES (30137, 32544);
INSERT INTO `pool_quest_save` VALUES (30137, 32733);
INSERT INTO `pool_quest_save` VALUES (30138, 32204);
INSERT INTO `pool_quest_save` VALUES (30138, 32254);
INSERT INTO `pool_quest_save` VALUES (30138, 32299);
INSERT INTO `pool_quest_save` VALUES (30139, 32537);
INSERT INTO `pool_quest_save` VALUES (30139, 32546);
INSERT INTO `pool_quest_save` VALUES (30139, 32606);
INSERT INTO `pool_quest_save` VALUES (30140, 32219);
INSERT INTO `pool_quest_save` VALUES (30140, 32224);
INSERT INTO `pool_quest_save` VALUES (30140, 32225);
INSERT INTO `pool_quest_save` VALUES (30140, 32728);
INSERT INTO `pool_quest_save` VALUES (30141, 32525);
INSERT INTO `pool_quest_save` VALUES (30141, 32528);
INSERT INTO `pool_quest_save` VALUES (30141, 32531);
INSERT INTO `pool_quest_save` VALUES (30141, 32731);
INSERT INTO `pool_quest_save` VALUES (30142, 32293);
INSERT INTO `pool_quest_save` VALUES (30143, 32576);
INSERT INTO `pool_quest_save` VALUES (30145, 32301);
INSERT INTO `pool_quest_save` VALUES (30145, 32485);
INSERT INTO `pool_quest_save` VALUES (30145, 32627);
INSERT INTO `pool_quest_save` VALUES (30145, 32628);
INSERT INTO `pool_quest_save` VALUES (30145, 32633);
INSERT INTO `pool_quest_save` VALUES (30145, 32637);
INSERT INTO `pool_quest_save` VALUES (30146, 32265);
INSERT INTO `pool_quest_save` VALUES (30146, 32268);
INSERT INTO `pool_quest_save` VALUES (30146, 32288);
INSERT INTO `pool_quest_save` VALUES (30146, 32300);
INSERT INTO `pool_quest_save` VALUES (30146, 32302);
INSERT INTO `pool_quest_save` VALUES (30146, 32305);
INSERT INTO `pool_quest_save` VALUES (30147, 32572);
INSERT INTO `pool_quest_save` VALUES (30147, 32574);
INSERT INTO `pool_quest_save` VALUES (30148, 32228);
INSERT INTO `pool_quest_save` VALUES (30148, 32506);
INSERT INTO `pool_quest_save` VALUES (30149, 32551);
INSERT INTO `pool_quest_save` VALUES (30149, 32552);
INSERT INTO `pool_quest_save` VALUES (30149, 32554);
INSERT INTO `pool_quest_save` VALUES (30150, 32283);
INSERT INTO `pool_quest_save` VALUES (30150, 32297);
INSERT INTO `pool_quest_save` VALUES (30150, 32298);
INSERT INTO `pool_quest_save` VALUES (30151, 32556);
INSERT INTO `pool_quest_save` VALUES (30151, 32558);
INSERT INTO `pool_quest_save` VALUES (30151, 32559);
INSERT INTO `pool_quest_save` VALUES (30152, 32206);
INSERT INTO `pool_quest_save` VALUES (30152, 32493);
INSERT INTO `pool_quest_save` VALUES (30152, 32494);
INSERT INTO `pool_quest_save` VALUES (30153, 32209);
INSERT INTO `pool_quest_save` VALUES (30154, 32588);
INSERT INTO `pool_quest_save` VALUES (30155, 32677);
INSERT INTO `pool_quest_save` VALUES (30156, 32608);

SET FOREIGN_KEY_CHECKS = 1;
