--实验六

--创建员工表
create table H_Staff_Info(
	StaffID varchar(10) primary key,
	StaffName nvarchar(10) not null, 
	Sex varchar(10) not null,
	Birthday date null, 
	GongLing int null, 
	Pasword varchar(6) null,
	Tel nvarchar(20) not null,
	BeiZhu text null,
)

--创建客户表
create table H_Customer_Info(
	CustomerID varchar(10) primary key,
	CustomerName nvarchar(10) not null,
	Sex varchar(10) not null,
	Birthday date null,
	IDCard varchar(18) null,
	Tel nvarchar(20) not null,
	BeiZhu text null,
)

--创建客房表
create table H_Room_Info(
	RoomID varchar(6) primary key, 
	StyleID varchar(4) not null,
	States varchar(4) not null,
	BeiZhu text null,
	FOREIGN KEY(StyleID) REFERENCES H_Style_Info (StyleID),
)

--创建类型表
create table H_Style_Info(
	StyleID varchar(4) primary key,
	StyleName nvarchar(16) not null,
	prices int null,
	total int null,
	remain int null,
	BeiZhu text null,
)

--创建订单表
create table H_Order_Info(
	OrderID varchar(10) primary key,
	StaffID varchar(10) not null,
	CustomerID varchar(10) not null,
	RoomID varchar(6) not null,
	YaJin int null,
	BeiZhu text null,
	FOREIGN KEY(StaffID) REFERENCES H_Staff_Info(StaffID),
	FOREIGN KEY(CustomerID) REFERENCES H_Customer_Info(CustomerID)
)

--创建退房表
create table H_Tui_Info(
	StaffID varchar(10) not null,
	CustomerID varchar(10) not null,
	RoomID varchar(6) not null,
	Tuidate Smalldatetime null,
	PRIMARY KEY(StaffID,CustomerID,RoomID),
	FOREIGN KEY(StaffID) REFERENCES H_Staff_Info(StaffID),
	FOREIGN KEY(CustomerID) REFERENCES H_Customer_Info(CustomerID),
	FOREIGN KEY(RoomID) REFERENCES H_Room_Info(RoomID)
)


CREATE INDEX staff ON H_Staff_Info(StaffID ASC)
CREATE UNIQUE INDEX ordedr ON H_Order_Info(OrderID ASC)

DROP INDEX H_Order_Info.ordedr

--插入操作（插入一条新的职工信息到员工表）
insert 
into H_Staff_Info
values ('10006','职工6','女','2001-06-06','2','10091','13644774569','努力')

--更新操作（将职工号为10006的员工的工龄更改为3）
update H_Staff_Info
set GongLing=3
where StaffID=10006

--删除操作（将职工号为10006的职工信息删除）
delete
from H_Staff_Info
where StaffID=10006

--连接查询：（两表连接）查询为00001号顾客登记订单的员工的详细情况
select S.*
from H_Staff_Info S,H_Order_Info O
where S.StaffID=O.StaffID and O.CustomerID=00001

--连接查询：（四表连接）查询入住002客房的订单编号，房间类型，以及客户姓名
select O.OrderID,ST.StyleName,C.CustomerID
from H_Order_Info O,H_Room_Info R,H_Customer_Info C,H_Style_Info ST
where O.RoomID=002 and O.CustomerID=C.CustomerID and
		R.RoomID = O.RoomID and R.StyleID=ST.StyleID

--嵌套查询：查询登记过退订订单的员工的现有订单情况
select *
from H_Order_Info O
where O.StaffID IN 
		(select T.StaffID
		from H_Tui_Info T
		)

--聚集函数使用：查询酒店房间的入住数量
select count(*)
from H_Room_Info R
where R.States='入住'

--不相关子查询：查询工龄大于5年的员工的现有订单登记情况
select *
from H_Order_Info O
where O.StaffID IN
		(select S.StaffID
		from H_Staff_Info S
		where S.GongLing>5
		)

--相关子查询：查询工龄大于5年的员工的现有订单登记情况
select *
from H_Order_Info O
where exists
		(select *
		from H_Staff_Info S
		where S.GongLing>5 and
				O.StaffID=S.StaffID
		)

--创建视图：创建工龄大于5年的员工信息视图
create view Older_Staff
As
select *
from H_Staff_Info S
where S.GongLing>=5
