create table mail_external
(
	id bigint unsigned auto_increment
		primary key,
	receiver bigint unsigned not null,
	subject varchar(200) default 'Support Message' null,
	message varchar(500) default 'Support Message' null,
	money bigint unsigned default 0 not null,
	item bigint unsigned default 0 not null,
	item_count bigint unsigned default 0 not null
);
