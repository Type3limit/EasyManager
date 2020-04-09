/*
 Navicat Premium Data Transfer

 Source Server         : mysql
 Source Server Type    : MySQL
 Source Server Version : 50728
 Source Host           : localhost:3306
 Source Schema         : easymanager

 Target Server Type    : MySQL
 Target Server Version : 50728
 File Encoding         : 65001

 Date: 09/04/2020 17:18:34
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for createinfo
-- ----------------------------
DROP TABLE IF EXISTS `createinfo`;
CREATE TABLE `createinfo`  (
  `create_id` int(11) NOT NULL COMMENT '编号',
  `create_table_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '表名',
  `create_segements` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '创建表的语句',
  PRIMARY KEY (`create_id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for customamount
-- ----------------------------
DROP TABLE IF EXISTS `customamount`;
CREATE TABLE `customamount`  (
  `custom_id` int(11) NOT NULL COMMENT '会员编号',
  `custom_amount` int(11) NOT NULL COMMENT '会员余额',
  PRIMARY KEY (`custom_id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for customationinfo
-- ----------------------------
DROP TABLE IF EXISTS `customationinfo`;
CREATE TABLE `customationinfo`  (
  `consume_id` int(11) NOT NULL AUTO_INCREMENT COMMENT '账单信息编号',
  `consume_custom_id` int(11) NOT NULL COMMENT '会员编号',
  `consume_product_id` int(11) NOT NULL COMMENT '商品编号',
  `consume_custom_amount` int(11) NOT NULL COMMENT '消费金额',
  `consume_time` datetime(0) NOT NULL COMMENT '消费发生时间',
  PRIMARY KEY (`consume_id`) USING BTREE,
  INDEX `CustomID`(`consume_custom_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for customerinfo
-- ----------------------------
DROP TABLE IF EXISTS `customerinfo`;
CREATE TABLE `customerinfo`  (
  `customer_id` int(11) NOT NULL AUTO_INCREMENT COMMENT '会员编号',
  `customer_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '会员名称',
  `customer_contanct` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '联系方式',
  `customer_password` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '会员密码',
  `customer_regist_time` datetime(0) NOT NULL COMMENT '会员注册时间',
  PRIMARY KEY (`customer_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for productcountinfo
-- ----------------------------
DROP TABLE IF EXISTS `productcountinfo`;
CREATE TABLE `productcountinfo`  (
  `product_id` int(11) NOT NULL COMMENT '商品编号',
  `product_count` int(11) NOT NULL COMMENT '商品数量',
  PRIMARY KEY (`product_id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for productininfo
-- ----------------------------
DROP TABLE IF EXISTS `productininfo`;
CREATE TABLE `productininfo`  (
  `productin_id` int(11) NOT NULL COMMENT '入库信息编号',
  `productin_product_id` int(11) NOT NULL COMMENT '商品编号',
  `productin_product_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '商品名称',
  `productin_product_type` tinyint(1) NOT NULL COMMENT '入库类型（新增和进货）',
  `productin_product_number` int(11) NOT NULL COMMENT '入库数量',
  `productin_product_cost` int(11) NOT NULL COMMENT '进货单价',
  PRIMARY KEY (`productin_id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for productoutinfo
-- ----------------------------
DROP TABLE IF EXISTS `productoutinfo`;
CREATE TABLE `productoutinfo`  (
  `productout_id` int(11) NOT NULL COMMENT '商品出库编号',
  `productout_product_id` int(11) NOT NULL COMMENT '商品编号',
  `productout_number` int(11) NOT NULL COMMENT '出库数量',
  `productout_cost` int(11) NOT NULL COMMENT '出库单价',
  PRIMARY KEY (`productout_id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for productsinfo
-- ----------------------------
DROP TABLE IF EXISTS `productsinfo`;
CREATE TABLE `productsinfo`  (
  `product_id` int(11) NOT NULL AUTO_INCREMENT COMMENT '商品编号',
  `product_cost` int(11) NOT NULL COMMENT '商品价格',
  `product_info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '商品信息',
  `product_image` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '商品图片存储路径',
  `product_useable` tinyint(1) NOT NULL COMMENT '是否可用',
  PRIMARY KEY (`product_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for queueinfo
-- ----------------------------
DROP TABLE IF EXISTS `queueinfo`;
CREATE TABLE `queueinfo`  (
  `queue_acount` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '使用者账号',
  `queue_current` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '队列现状',
  PRIMARY KEY (`queue_acount`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for rechargeinfo
-- ----------------------------
DROP TABLE IF EXISTS `rechargeinfo`;
CREATE TABLE `rechargeinfo`  (
  `recharge_id` int(11) NOT NULL COMMENT '充值账单编号',
  `recharge_customer_id` int(11) NOT NULL COMMENT '会员编号',
  `recharge_acount` int(11) NOT NULL COMMENT '充值金额',
  `recharge_after_money` int(11) NOT NULL COMMENT '充值后金额',
  `recharge_action_time` datetime(0) NOT NULL COMMENT '交易发生时间',
  PRIMARY KEY (`recharge_id`) USING BTREE,
  INDEX `Custom`(`recharge_customer_id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for userinfo
-- ----------------------------
DROP TABLE IF EXISTS `userinfo`;
CREATE TABLE `userinfo`  (
  `user_account` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '用户账号',
  `user_password` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '用户密码',
  `user_regist_time` datetime(0) NOT NULL COMMENT '注册时间',
  `user_login` tinyint(1) NOT NULL COMMENT '是否登录',
  `user_model_choose` int(11) NOT NULL COMMENT '是否选择模块',
  `user_question` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '密保问题',
  `user_answer` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '密保答案',
  PRIMARY KEY (`user_account`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
