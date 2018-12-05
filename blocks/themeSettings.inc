<?php



/**
 * Implements HOOK_preprocess_hook
 */

function p1base_preprocess(&$variables, $hook)
{


  /**
   * A bit hacky, but this is the easiest way to preprocess all blocks only.
   * Preprocess that runs for all templates does not hook into a specific block
   * type, and only hooks into the specific name for the template block, so we
   * have to utilise this way to preprocess all blocks - using this hook, which
   * runs for EVERY template, then within this hook, narrow down the custom
   * blocks.
   *
   *  FIXME:  Is there some other way to do the preprocessing based on the bundle
   * name of the block? Is that achievable?
   */

  /**
   *  NOTE:  in Drupal 8, BLOCK entities and CUSTOM BLOCK entities are ** DIFFERENT **.
   * The normal block entities are called 'block' - this is the base that is
   * inherited by all blocks (even the custom ones, or those provided by a
   * different module) on the site.
   * The custom blocks that we create a type for, AND the 'Basic Block' Custom
   * Blocks, are all instances of an entity called 'Block Content' and are
   * handled by the module named Block Content (it's in Drupal Core).
   */


  /**
   * A bit hacky, but this is the easiest way to preprocess all blocks only.
   * Preprocess that runs for all templates does not hook into a specific block
   * type, and only hooks into the specific name for the template block, so we
   * have to utilise this way to preprocess all blocks - using this hook, which
   * runs for EVERY template, then within this hook, narrow down the custom
   * blocks.
   *
   *  FIXME:  Is there some other way to do the preprocessing based on the bundle
   * name of the block? Is that achievable?
   */

  /**
   *  NOTE:  in Drupal 8, BLOCK entities and CUSTOM BLOCK entities are ** DIFFERENT **.
   * The normal block entities are called 'block' - this is the base that is
   * inherited by all blocks (even the custom ones, or those provided by a
   * different module) on the site.
   * The custom blocks that we create a type for, AND the 'Basic Block' Custom
   * Blocks, are all instances of an entity called 'Block Content' and are
   * handled by the module named Block Content (it's in Drupal Core).
   */

  if ($hook == 'block') { // Check that the template is for a block
    if ($variables['elements']['#base_plugin_id'] == 'block_content') { // Make sure it's a custom block entity type.

      /**
       * Passing down the theme setting values to custom blocks so that they can
       * utilise the social media / address values.
       */
      $address_details = [
        'address_line_1',
        'address_line_2',
        'address_line_3',
        'address_line_4',
        'address_line_5',
        'e_mail',
        'phone_number',
      ];

      $online_details = [
        'youtube_url',
        'pinterest_url',
        'twitter_url',
        'instagram_url',
        'facebook_url',
      ];

      $address = array();

      foreach ($address_details as $item) {
        $address[$item] = theme_get_setting($item);
      };

      foreach ($online_details as $item) {
        $online_contact_details[$item] = theme_get_setting($item);
      };

      $variables['address'] = $address;
      $variables['online_contact_details'] = $online_contact_details;

    }
  }
}