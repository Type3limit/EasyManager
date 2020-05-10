/*
 Navicat Premium Data Transfer

 Source Server         : newsql
 Source Server Type    : MySQL
 Source Server Version : 80019
 Source Host           : 39.97.210.220:3306
 Source Schema         : EasyManager

 Target Server Type    : MySQL
 Target Server Version : 80019
 File Encoding         : 65001

 Date: 06/05/2020 12:02:28
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for createinfo
-- ----------------------------
DROP TABLE IF EXISTS `createinfo`;
CREATE TABLE `createinfo`  (
  `create_id` int(0) NOT NULL COMMENT '编号',
  `create_table_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '表名',
  `create_segements` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '创建表的语句',
  PRIMARY KEY (`create_id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of createinfo
-- ----------------------------

-- ----------------------------
-- Table structure for customationinfo
-- ----------------------------
DROP TABLE IF EXISTS `customationinfo`;
CREATE TABLE `customationinfo`  (
  `consume_id` int(0) NOT NULL AUTO_INCREMENT COMMENT '账单信息编号',
  `consume_custom_id` int(0) NOT NULL COMMENT '会员编号',
  `consume_product_id` int(0) NOT NULL COMMENT '商品编号',
  `consume_custom_amount` double(11, 0) NOT NULL COMMENT '消费金额',
  `consume_time` datetime(0) NOT NULL COMMENT '消费发生时间',
  `consume_count` int(0) NOT NULL COMMENT '消费数量\r\n',
  PRIMARY KEY (`consume_id`) USING BTREE,
  INDEX `CustomID`(`consume_custom_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of customationinfo
-- ----------------------------

-- ----------------------------
-- Table structure for customeramount
-- ----------------------------
DROP TABLE IF EXISTS `customeramount`;
CREATE TABLE `customeramount`  (
  `customer_id` int(0) NOT NULL COMMENT '会员编号',
  `customer_amount` double(11, 2) NOT NULL COMMENT '会员余额',
  PRIMARY KEY (`customer_id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of customeramount
-- ----------------------------
INSERT INTO `customeramount` VALUES (11, 0.00);
INSERT INTO `customeramount` VALUES (14, 381.00);
INSERT INTO `customeramount` VALUES (15, 11.00);

-- ----------------------------
-- Table structure for customerinfo
-- ----------------------------
DROP TABLE IF EXISTS `customerinfo`;
CREATE TABLE `customerinfo`  (
  `customer_id` int(0) NOT NULL AUTO_INCREMENT COMMENT '会员编号',
  `customer_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '会员名称',
  `customer_contanct` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '联系方式',
  `customer_password` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '会员密码',
  `customer_regist_time` datetime(0) NOT NULL COMMENT '会员注册时间',
  PRIMARY KEY (`customer_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 17 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of customerinfo
-- ----------------------------
INSERT INTO `customerinfo` VALUES (11, '123', '123', '123', '2020-04-17 15:04:00');
INSERT INTO `customerinfo` VALUES (14, 'ax', 'aaa', '123', '2020-04-20 10:04:00');
INSERT INTO `customerinfo` VALUES (15, '测试用户1', '123', '123', '2020-05-03 22:05:00');
INSERT INTO `customerinfo` VALUES (16, '测试用户2', '123', '123', '2020-05-03 22:05:00');

-- ----------------------------
-- Table structure for modelinfo
-- ----------------------------
DROP TABLE IF EXISTS `modelinfo`;
CREATE TABLE `modelinfo`  (
  `model_user_id` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '用户名称',
  `model_customer_manage` tinyint(1) NOT NULL DEFAULT 0 COMMENT '是否选择会员信息管理模块',
  `model_product_manage` tinyint(1) NOT NULL DEFAULT 0 COMMENT '是否选择商品信息管理模块',
  `model_hold_queue` tinyint(1) NOT NULL DEFAULT 0 COMMENT '是否选择等待队列模块',
  `model_reserve` tinyint(1) NOT NULL DEFAULT 0 COMMENT '是否选择预约模块',
  `model_sell` tinyint(1) NOT NULL DEFAULT 0 COMMENT '是否选择使用者消费模块\r\n',
  PRIMARY KEY (`model_user_id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of modelinfo
-- ----------------------------
INSERT INTO `modelinfo` VALUES ('0', 1, 1, 1, 1, 1);
INSERT INTO `modelinfo` VALUES ('123', 1, 1, 1, 1, 1);
INSERT INTO `modelinfo` VALUES ('123123', 1, 0, 1, 0, 1);
INSERT INTO `modelinfo` VALUES ('1234', 1, 0, 1, 0, 1);
INSERT INTO `modelinfo` VALUES ('4123', 1, 1, 1, 1, 1);
INSERT INTO `modelinfo` VALUES ('444', 0, 1, 1, 1, 1);
INSERT INTO `modelinfo` VALUES ('666', 1, 1, 1, 1, 1);
INSERT INTO `modelinfo` VALUES ('ax', 1, 1, 1, 1, 1);
INSERT INTO `modelinfo` VALUES ('hjy', 0, 0, 0, 0, 0);
INSERT INTO `modelinfo` VALUES ('测试机', 1, 1, 1, 1, 1);
INSERT INTO `modelinfo` VALUES ('邱强', 1, 1, 1, 1, 1);

-- ----------------------------
-- Table structure for productcountinfo
-- ----------------------------
DROP TABLE IF EXISTS `productcountinfo`;
CREATE TABLE `productcountinfo`  (
  `product_id` int(0) NOT NULL COMMENT '商品编号',
  `product_count` int(0) NOT NULL COMMENT '商品数量',
  PRIMARY KEY (`product_id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of productcountinfo
-- ----------------------------
INSERT INTO `productcountinfo` VALUES (16, 12);
INSERT INTO `productcountinfo` VALUES (17, 11);

-- ----------------------------
-- Table structure for productininfo
-- ----------------------------
DROP TABLE IF EXISTS `productininfo`;
CREATE TABLE `productininfo`  (
  `productin_id` int(0) NOT NULL AUTO_INCREMENT COMMENT '入库信息编号',
  `productin_product_id` int(0) NOT NULL COMMENT '商品编号',
  `productin_product_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '商品名称',
  `productin_product_type` tinyint(1) NOT NULL COMMENT '入库类型（新增和进货）',
  `productin_product_number` int(0) NOT NULL COMMENT '入库数量',
  `productin_product_cost` int(0) NOT NULL COMMENT '进货单价',
  PRIMARY KEY (`productin_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 7 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of productininfo
-- ----------------------------
INSERT INTO `productininfo` VALUES (4, 16, '小老板', 0, 11, 11);
INSERT INTO `productininfo` VALUES (5, 16, '小老板', 1, 12, 12);
INSERT INTO `productininfo` VALUES (6, 17, '测试商品', 0, 11, 11);

-- ----------------------------
-- Table structure for productoutinfo
-- ----------------------------
DROP TABLE IF EXISTS `productoutinfo`;
CREATE TABLE `productoutinfo`  (
  `productout_id` int(0) NOT NULL AUTO_INCREMENT COMMENT '商品出库编号',
  `productout_product_id` int(0) NOT NULL COMMENT '商品编号',
  `productout_number` int(0) NOT NULL COMMENT '出库数量',
  `productout_cost` int(0) NOT NULL COMMENT '出库单价',
  PRIMARY KEY (`productout_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 2 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of productoutinfo
-- ----------------------------
INSERT INTO `productoutinfo` VALUES (1, 16, 11, 12);

-- ----------------------------
-- Table structure for productsinfo
-- ----------------------------
DROP TABLE IF EXISTS `productsinfo`;
CREATE TABLE `productsinfo`  (
  `product_id` int(0) NOT NULL AUTO_INCREMENT COMMENT '商品编号',
  `product_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '商品名称',
  `product_image` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '商品图片路径\r\n\r\n',
  `product_cost` double(11, 2) NOT NULL COMMENT '商品价格',
  `product_info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '商品信息',
  `product_useable` tinyint(1) NOT NULL DEFAULT 1 COMMENT '是否可用',
  PRIMARY KEY (`product_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 18 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of productsinfo
-- ----------------------------
INSERT INTO `productsinfo` VALUES (16, '小老板', '', 12.00, '小老板', 1);
INSERT INTO `productsinfo` VALUES (17, '测试商品', 'D:/pic/32-1Q119140142308.jpg', 11.00, '测试用', 1);

-- ----------------------------
-- Table structure for queueinfo
-- ----------------------------
DROP TABLE IF EXISTS `queueinfo`;
CREATE TABLE `queueinfo`  (
  `queue_costumer_id` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '会员编号',
  `queue_next_id` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '下一位',
  `queue_previous_id` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '上一位',
  PRIMARY KEY (`queue_costumer_id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of queueinfo
-- ----------------------------

-- ----------------------------
-- Table structure for rechargeinfo
-- ----------------------------
DROP TABLE IF EXISTS `rechargeinfo`;
CREATE TABLE `rechargeinfo`  (
  `recharge_id` int(0) NOT NULL AUTO_INCREMENT COMMENT '充值账单编号',
  `recharge_customer_id` int(0) NOT NULL COMMENT '会员编号',
  `recharge_acount` int(0) NOT NULL COMMENT '充值金额',
  `recharge_action_time` datetime(0) NOT NULL COMMENT '交易发生时间',
  PRIMARY KEY (`recharge_id`) USING BTREE,
  INDEX `Custom`(`recharge_customer_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 5 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of rechargeinfo
-- ----------------------------
INSERT INTO `rechargeinfo` VALUES (1, 14, 123, '2020-04-20 11:04:00');
INSERT INTO `rechargeinfo` VALUES (2, 14, 12, '2020-04-20 11:04:00');
INSERT INTO `rechargeinfo` VALUES (3, 14, 123, '2020-05-03 21:05:00');
INSERT INTO `rechargeinfo` VALUES (4, 15, 11, '2020-05-03 22:05:00');

-- ----------------------------
-- Table structure for reserveinfo
-- ----------------------------
DROP TABLE IF EXISTS `reserveinfo`;
CREATE TABLE `reserveinfo`  (
  `reserve_id` int(0) NOT NULL AUTO_INCREMENT COMMENT '预约编号',
  `reserve_customer_id` int(0) NOT NULL COMMENT '预约的客户编号\r\n',
  `reserve_contain` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '预约的内容',
  PRIMARY KEY (`reserve_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of reserveinfo
-- ----------------------------

-- ----------------------------
-- Table structure for userinfo
-- ----------------------------
DROP TABLE IF EXISTS `userinfo`;
CREATE TABLE `userinfo`  (
  `user_account` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '用户账号',
  `user_password` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '用户密码',
  `user_regist_time` datetime(0) NOT NULL COMMENT '注册时间',
  `user_login` tinyint(1) NOT NULL COMMENT '是否登录',
  `user_model_choose` tinyint(1) NOT NULL COMMENT '是否进行了客制化\r\n',
  `user_question` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '密保问题',
  `user_answer` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '密保答案',
  PRIMARY KEY (`user_account`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of userinfo
-- ----------------------------
INSERT INTO `userinfo` VALUES ('0000', '0000', '2020-04-10 14:04:00', 0, 1, '0000', '0000');
INSERT INTO `userinfo` VALUES ('100', '100', '2020-04-17 10:04:00', 0, 0, '100', '100');
INSERT INTO `userinfo` VALUES ('123', '12345', '2020-04-09 11:04:00', 1, 1, '123', '123');
INSERT INTO `userinfo` VALUES ('123123', '123123', '2020-04-09 17:04:00', 0, 1, '123123', '123123');
INSERT INTO `userinfo` VALUES ('123123123', '123123123', '2020-04-09 17:04:00', 0, 0, '123123123', '123123123');
INSERT INTO `userinfo` VALUES ('1234', '1234', '2020-04-09 11:04:00', 0, 1, '1234', '1234');
INSERT INTO `userinfo` VALUES ('4123', '4123', '2020-04-09 15:04:00', 0, 1, '4123', '4123');
INSERT INTO `userinfo` VALUES ('444', '444', '2020-04-09 16:04:00', 0, 1, '444', '444');
INSERT INTO `userinfo` VALUES ('666', '666', '2020-04-09 15:04:00', 0, 1, '666', '666');
INSERT INTO `userinfo` VALUES ('ax', '123', '2020-04-10 11:04:00', 0, 1, 'ax', 'ax');
INSERT INTO `userinfo` VALUES ('hjy', '123', '2020-04-21 19:04:00', 0, 1, '123', '123');
INSERT INTO `userinfo` VALUES ('nice', 'good', '1998-03-07 12:00:00', 0, 0, 'Question', 'Anwser');
INSERT INTO `userinfo` VALUES ('测试机', '123', '2020-04-21 18:04:00', 0, 1, '123', '123');
INSERT INTO `userinfo` VALUES ('测试用户', '123123', '2020-04-09 16:04:00', 0, 0, '123123', '123123');
INSERT INTO `userinfo` VALUES ('邱强', '12345', '2020-04-21 19:04:00', 0, 1, '123', '123');

SET FOREIGN_KEY_CHECKS = 1;
