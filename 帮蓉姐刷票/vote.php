<?php 
	$countvote=10;
	$errno = '';
	$errstr = '';
	//Ҫpost������
	$post ='optArr%5B%5D=146&vote_id=39';
    $length = strlen($post);
	
    //����post�����ͷ
    $header  = "POST http://weixin.xdkexie.com/index.php?s=/addon/Vote/Vote/join.html HTTP/1.1\r\n";
    $header .= "Host:weixin.xdkexie.com\r\n";
    $header .= "User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:31.0) Gecko/20100101 Firefox/31.0\r\n";
    $header .= "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n";
	$header .= "Accept-Language: zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3\r\n";
	$header .= "Accept-Encoding: gzip, deflate\r\n";
	$header .= "DNT: 1\r\n";	
	$header .= "Connection: keep-alive\r\n";
    $header .= "Content-Type: application/x-www-form-urlencoded\r\n";	
    $header .= "Content-Length: ".$length."\r\n";
    $header .= "Connection: Close\r\n\r\n";    
    $header .= $post."\r\n";		//���post���ַ���
	while($countvote!=0)
	{	    
	$fp = fsockopen("weixin.xdkexie.com",80,$errno,$errstr,10) or exit($errstr."--->".$errno);//����socket����   
	fputs($fp,$header); //����post������
	$inheader = 1;
    while (!feof($fp)) {
        $line = fgets($fp,1024); //ȥ���������ͷֻ��ʾҳ��ķ�������
		echo $line;
        
    }
	$countvote-=1;
	fclose($fp);
	}	
?>