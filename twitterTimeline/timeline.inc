<?php

require "vendor/autoload.php";

use Abraham\TwitterOAuth\TwitterOAuth;


/**
 * Implements HOOK_preprocess_HOOK
 *
 * This code utilises the TwitterOAuth library to make requests to the Twitter
 * API. The settings for the user are all here - could we utilise the
 * theme settings to make this easier to configure? Can we fil
 */
function p1base_preprocess_block__tweetslist(&$variables) {


  $consumer_key = theme_get_setting('consumer_key');
  $consumer_secret = theme_get_setting('consumer_secret');

  $access_token = theme_get_setting('access_token');
  $access_token_secret = theme_get_setting('access_token_secret');

  $twitter_user_id = theme_get_setting('twitter_user_id');


  $connection = new TwitterOAuth($consumer_key, $consumer_secret, $access_token, $access_token_secret);
  $content = $connection->get("account/verify_credentials");
  $statuses = $connection->get("statuses/user_timeline", ["user_id" => $twitter_user_id, "count" => "2", "tweet_mode" => "extended"]);

  $tweets = [];

  foreach ($statuses as $status) {
    $tweet = [];

    $raw_text = $status->full_text;
    $text_copy = $raw_text;

    $entities = $status->entities;

    $user_mentions = $entities->user_mentions;
    $hashtags = $entities->hashtags;
    $symbols = $entities->symbols;
    $urls = $entities->urls;

    foreach($user_mentions as $user_mention) {
      $name = $user_mention->screen_name;
      $id_str = $user_mention->id_str;
      $link_url = "http://twitter.com/intent/user?user_id={$id_str}";
      $link_replace_start = $user_mention->indices['0'];
      $link_replace_end = $user_mention->indices['1'];
      $link_replace_length = $link_replace_end - $link_replace_start;
      $link_text = substr($raw_text, $link_replace_start, $link_replace_length);
      $link_html = "<a target='_blank' class='f-heading' href='{$link_url}'>{$link_text}</a>";
      $text_copy = str_replace($link_text, $link_html, $text_copy);
    }

    foreach($hashtags as $hashtag) {
      $name = $hashtag->text;
      $link_url = "http://twitter.com/hashtag/{$name}?src=hash";
      $link_replace_start = $hashtag->indices['0'];
      $link_replace_end = $hashtag->indices['1'];
      $link_replace_length = $link_replace_end - $link_replace_start;
      $link_text = substr($raw_text, $link_replace_start, $link_replace_length);
      $link_html = "<a target='_blank' class='f-heading' href='{$link_url}'>{$link_text}</a>";
      $text_copy = str_replace($link_text, $link_html, $text_copy);
    }
    foreach($urls as $url) {
      $name = $url->url;
      $link_url = $url->expanded_url;
      $link_replace_start = $url->indices['0'];
      $link_replace_end = $url->indices['1'];
      $link_replace_length = $link_replace_end - $link_replace_start;
      $link_text = substr($raw_text, $link_replace_start, $link_replace_length);
      $link_html = "<a target='_blank' class='f-heading' href='{$link_url}'>{$name}</a>";
      $text_copy = str_replace($link_text, $link_html, $text_copy);
    }

    $text_copy = "<p class='mb0'>{$text_copy}</p>";

    $tweet['text'] = $text_copy;

    $tweet['id_str'] = $status->id_str;

    $tweet['more_link'] = "<p class='mt0 text-right'><a class='fs-small f-heading' target='_blank' href='https://twitter.com/statuses/{$status->id_str}'>Read more...</a></p>";
    $tweets[] = $tweet;
  }
  $variables['tweets'] = $tweets;
}