/* 新建表。
 * <http://sqlite.org/lang_createtable.html>
 */
CREATE TABLE IF NOT EXISTS 'table' (
  id    INTEGER CONSTRAINT pk_table_id PRIMARY KEY AUTOINCREMENT,
  intc  INTEGER,
  realc REAL,
  txtc  TEXT,
  blobc BLOB
);

-- 示例
CREATE TABLE IF NOT EXISTS interface (
  id      INTEGER CONSTRAINT pk_interface_id PRIMARY KEY AUTOINCREMENT,
  brief   TEXT CONSTRAINT uq_interface_brief UNIQUE,
  details TEXT
);

CREATE TABLE IF NOT EXISTS environment (
  id          INTEGER CONSTRAINT pk_environment_id PRIMARY KEY AUTOINCREMENT,
  description TEXT CONSTRAINT uq_environment_description UNIQUE
);

CREATE TABLE IF NOT EXISTS implementation (
  id            INTEGER CONSTRAINT pk_implementation_id PRIMARY KEY AUTOINCREMENT,
  interfaceid   INTEGER,
  environmentid INTEGER,
  operation     TEXT CONSTRAINT uq_implementation UNIQUE,
  CONSTRAINT fk_implementation_interface FOREIGN KEY (interfaceid) REFERENCES interface (id),
  CONSTRAINT fk_implementation_environment FOREIGN KEY (environmentid) REFERENCES environment (id)
);


/* 删除表。
 * <http://sqlite.org/lang_droptable.html>
 */
DROP TABLE IF EXISTS 'table';
