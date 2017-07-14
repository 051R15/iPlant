<?php
my_log(
  log_id int(11)
  remote_addr varchar(255) '',
  request_uri varchar(255) '',
  message text '',
  log_date timestamp NOW(),
  (log_id)

  ) TYPE = MyISAM COMMENT='log';
 ?>
