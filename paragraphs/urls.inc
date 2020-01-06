<?php 
if ($paragraphType == 'fp_link') {
    $field_any_link = $paragraph->field_any_link;
    $uri = $field_any_link->uri;
    $url = Url::fromUri($uri);
    $variables['url'] = $url->toString();
  }