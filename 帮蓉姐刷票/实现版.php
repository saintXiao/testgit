 <?php  
    
	/*
	//require dirname(__FILE__).'/function.php';  
    $countvote=10;
	$a=13829331234;
	$b=time();
    function curl_post($url, $post) {  
        $options = array(  
            CURLOPT_RETURNTRANSFER => true,  
            CURLOPT_HEADER         => false,  
            CURLOPT_POST           => true,  
            CURLOPT_POSTFIELDS     => $post,  
        );  
      
        $ch = curl_init($url);  
        curl_setopt_array($ch, $options);  
        $result = curl_exec($ch);  
        curl_close($ch);  
        return $result;
		echo $result;
    } 
		
	/*function file_get_contents_post($url, $post) {  
    $options = array(  
        'http' => array(  
            'method' => 'POST',  
            // 'content' => 'name=caiknife&email=caiknife@gmail.com',  
            'content' => http_build_query($post),  
        ),  
    );  
  
    $result = file_get_contents($url, false, stream_context_create($options));  
  
    return $result;  
	}*/
	
	/*
	while($countvote!=0){
    $data = curl_post("http://www.campus.kotex.com.cn/Interface/ajax/CommandService.aspx", array('key'=>'VoteApply', 'param'=>'{"TeamId":"175","Name":"����","Phone":"$a","Addr":"����"}','temp'=>'$b'));  
    //$data = file_get_contents_post("http://www.campus.kotex.com.cn/TeamShow.aspx?c=CD", array('key'=>'VoteApply', 'param'=>'{"TeamId":"175","Name":"������","Phone":"$a","Addr":"����"}','temp'=>'1416212138795'));
	$countvote-=1;
	$a+=1;
	echo $a."\r\n";
	} 
    //var_dump($data); 
	print_r($result);              
	*/ 
															/**********�������ķָ���***********/
	  //ǰ�漸��Ҳ�У������ֱ��� curlģ��post��file_get_contentsmonipost�����ߺ����е����⣡��
	$countvote=50;
	$a=18829302493;
	$b=time();
	    
	while($countvote!=0){
	$url = 'http://www.campus.kotex.com.cn/Interface/ajax/CommandService.aspx';  //���ýӿڵ�ƽ̨�����ַ  
    $post_string = array('key'=>'VoteApply', 'param'=>'{"TeamId":"175","Name":"��ѩ��","Phone":"'.$a.'","Addr":"����"}','temp'=>''.$b.'');// ���ݵ�������ͨ��������鿴���� //'.$a.'��������Ҫ����д����
    $ch = curl_init();  
    curl_setopt($ch, CURLOPT_URL, $url);  
    curl_setopt($ch, CURLOPT_POSTFIELDS, $post_string);  
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);  
    curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 10);  
    curl_setopt($ch, CURLOPT_TIMEOUT, 30);  
    $result = curl_exec($ch);
	$a=$a+3;
	//$b+=10;
	$countvote-=1;
	echo $a;
	//echo $b;
	echo $result;
    curl_close($ch); 
	}
	?>