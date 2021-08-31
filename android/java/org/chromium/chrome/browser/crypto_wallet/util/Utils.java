/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.crypto_wallet.util;

import static android.content.ClipDescription.MIMETYPE_TEXT_PLAIN;

import android.app.Activity;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.view.inputmethod.InputMethodManager;

import org.chromium.base.ContextUtils;
import org.chromium.brave_wallet.mojom.Network;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.crypto_wallet.activities.AccountDetailActivity;
import org.chromium.chrome.browser.crypto_wallet.activities.AddAccountActivity;
import org.chromium.chrome.browser.crypto_wallet.activities.AssetDetailActivity;
import org.chromium.chrome.browser.crypto_wallet.activities.BuySendSwapActivity;
import org.chromium.ui.widget.Toast;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Pattern;

public class Utils {
    public static final Pattern PASSWORD_PATTERN = Pattern.compile("^"
            + "(?=.*[0-9])" + // at least 1 digit
            "(?=.*[a-zA-Z])" + // any letter
            "(?=.*[$&+,:;=?@#|'<>.^*()%!-])" + // at least 1 special character
            "(?=\\S+$)" + // no white spaces
            ".{7,}" + // at least 7 characters
            "$");

    public static int ONBOARDING_ACTION = 1;
    public static int UNLOCK_WALLET_ACTION = 2;
    public static int RESTORE_WALLET_ACTION = 3;

    public static int ACCOUNT_ITEM = 1;
    public static int ASSET_ITEM = 2;
    public static int TRANSACTION_ITEM = 3;

    private static final String PREF_CRYPTO_ONBOARDING = "crypto_onboarding";

    public static List<String> getRecoveryPhraseAsList(String recoveryPhrase) {
        String[] recoveryPhraseArray = recoveryPhrase.split(" ");
        return new ArrayList<String>(Arrays.asList(recoveryPhraseArray));
    }

    public static String getRecoveryPhraseFromList(List<String> recoveryPhrases) {
        String recoveryPhrasesText = "";
        for (String phrase : recoveryPhrases) {
            recoveryPhrasesText = recoveryPhrasesText.concat(phrase).concat(" ");
        }
        return recoveryPhrasesText.trim();
    }

    public static void saveTextToClipboard(Context context, String textToCopy) {
        ClipboardManager clipboard =
                (ClipboardManager) context.getSystemService(Context.CLIPBOARD_SERVICE);
        ClipData clip = ClipData.newPlainText("", textToCopy);
        clipboard.setPrimaryClip(clip);
        Toast.makeText(context, R.string.text_has_been_copied, Toast.LENGTH_SHORT).show();
    }

    public static String getTextFromClipboard(Context context) {
        ClipboardManager clipboard =
                (ClipboardManager) context.getSystemService(Context.CLIPBOARD_SERVICE);
        String pasteData = "";
        if (!(clipboard.hasPrimaryClip())) {
            return pasteData;
        } else if (!(clipboard.getPrimaryClipDescription().hasMimeType(MIMETYPE_TEXT_PLAIN))) {
            return pasteData;
        } else {
            ClipData.Item item = clipboard.getPrimaryClip().getItemAt(0);
            return item.getText().toString();
        }
    }

    public static boolean shouldShowCryptoOnboarding() {
        SharedPreferences mSharedPreferences = ContextUtils.getAppSharedPreferences();
        return mSharedPreferences.getBoolean(PREF_CRYPTO_ONBOARDING, true);
    }

    public static void disableCryptoOnboarding() {
        SharedPreferences mSharedPreferences = ContextUtils.getAppSharedPreferences();
        SharedPreferences.Editor sharedPreferencesEditor = mSharedPreferences.edit();
        sharedPreferencesEditor.putBoolean(PREF_CRYPTO_ONBOARDING, false);
        sharedPreferencesEditor.apply();
    }

    public static void hideKeyboard(Activity activity) {
        InputMethodManager imm =
                (InputMethodManager) activity.getSystemService(Context.INPUT_METHOD_SERVICE);
        imm.hideSoftInputFromWindow(activity.getCurrentFocus().getWindowToken(), 0);
    }

    public static void openBuySendSwapActivity(
            Activity activity, BuySendSwapActivity.ActivityType activityType) {
        assert activity != null;
        Intent buySendSwapActivityIntent = new Intent(activity, BuySendSwapActivity.class);
        buySendSwapActivityIntent.putExtra("activityType", activityType.getValue());
        activity.startActivity(buySendSwapActivityIntent);
    }

    public static void openAssetDetailsActivity(Activity activity) {
        assert activity != null;
        Intent assetDetailIntent = new Intent(activity, AssetDetailActivity.class);
        activity.startActivity(assetDetailIntent);
    }

    public static void openAddAccountActivity(Activity activity) {
        assert activity != null;
        Intent addAccountActivityIntent = new Intent(activity, AddAccountActivity.class);
        activity.startActivity(addAccountActivityIntent);
    }

    public static void openAccountDetailActivity(Activity activity) {
        assert activity != null;
        Intent accountDetailActivityIntent = new Intent(activity, AccountDetailActivity.class);
        activity.startActivity(accountDetailActivityIntent);
    }

    public static List<String> getNetworksList(Activity activity) {
        List<String> categories = new ArrayList<String>();
        categories.add(activity.getText(R.string.mainnet).toString());
        categories.add(activity.getText(R.string.rinkeby).toString());
        categories.add(activity.getText(R.string.ropsten).toString());
        categories.add(activity.getText(R.string.goerli).toString());
        categories.add(activity.getText(R.string.kovan).toString());
        categories.add(activity.getText(R.string.localhost).toString());
        categories.add(activity.getText(R.string.custom).toString());

        return categories;
    }

    public static CharSequence getNetworkText(Activity activity, int network) {
        CharSequence strNetwork = activity.getText(R.string.mainnet);
        switch (network) {
            case Network.RINKEBY:
                strNetwork = activity.getText(R.string.rinkeby);
                break;
            case Network.ROPSTEN:
                strNetwork = activity.getText(R.string.ropsten);
                break;
            case Network.GOERLI:
                strNetwork = activity.getText(R.string.goerli);
                break;
            case Network.KOVAN:
                strNetwork = activity.getText(R.string.kovan);
                break;
            case Network.LOCALHOST:
                strNetwork = activity.getText(R.string.localhost);
                break;
            case Network.CUSTOM:
                strNetwork = activity.getText(R.string.custom);
                break;
            case Network.MAINNET:
            default:
                strNetwork = activity.getText(R.string.mainnet);
        }

        return strNetwork;
    }

    public static int getNetworkId(Activity activity, String network) {
        int networkId = Network.MAINNET;
        if (network.equals(activity.getText(R.string.rinkeby).toString())) {
            networkId = Network.RINKEBY;
        } else if (network.equals(activity.getText(R.string.ropsten).toString())) {
            networkId = Network.ROPSTEN;
        } else if (network.equals(activity.getText(R.string.goerli).toString())) {
            networkId = Network.GOERLI;
        } else if (network.equals(activity.getText(R.string.kovan).toString())) {
            networkId = Network.KOVAN;
        } else if (network.equals(activity.getText(R.string.localhost).toString())) {
            networkId = Network.LOCALHOST;
        } else if (network.equals(activity.getText(R.string.custom).toString())) {
            networkId = Network.CUSTOM;
        }

        return networkId;
    }
}
