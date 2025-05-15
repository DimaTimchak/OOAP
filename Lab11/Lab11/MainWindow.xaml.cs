using Microsoft.Web.WebView2.Core;
using System;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;

namespace Lab11
{
    public partial class MainWindow : Window
    {
        private readonly string[] products = { "iPhone 15", "PlayStation 5", "Samsung Galaxy S24" };

        public MainWindow()
        {
            InitializeComponent();
            InitBrowsers();
        }

        private async void InitBrowsers()
        {
            await webView1.EnsureCoreWebView2Async();
            await webView2.EnsureCoreWebView2Async();
            await webView3.EnsureCoreWebView2Async();
        }

        private async void Start_Click(object sender, RoutedEventArgs e)
        {
            resultsList.Items.Clear();

            // Fork:
            var tasks = new List<Task>
            {
                SearchAsync(webView1, products[0]),
                SearchAsync(webView2, products[1]),
                SearchAsync(webView3, products[2])
            };

            // Join:
            await Task.WhenAll(tasks);

            Dispatcher.Invoke(() =>
            {
                resultsList.Items.Add("🔍 Пошук завершено.");
            });
        }

        private async Task SearchAsync(Microsoft.Web.WebView2.Wpf.WebView2 webView, string productName)
        {
            string query = Uri.EscapeDataString(productName);
            string url = $"https://allo.ua/ua/catalogsearch/result/?q={query}";

            var tcs = new TaskCompletionSource<bool>();

            await Dispatcher.InvokeAsync(() =>
            {
                void Handler(object s, CoreWebView2NavigationCompletedEventArgs e)
                {
                    webView.CoreWebView2.NavigationCompleted -= Handler;
                    tcs.TrySetResult(true);
                }

                webView.CoreWebView2.NavigationCompleted += Handler;
                webView.CoreWebView2.Navigate(url);
            });

            await tcs.Task;

            string script = @"
                (function() {
                    let el = document.querySelector('.v-pb__cur');
                    return el ? el.innerText : 'Ціна не знайдена';
                })();";

            string result = await webView.Dispatcher.Invoke(async () =>
            {
                string raw = await webView.ExecuteScriptAsync(script);
                return Regex.Unescape(raw.Trim('"'));
            });

            Dispatcher.Invoke(() =>
            {
                resultsList.Items.Add($"{productName}: {result}");
            });
        }
    }
}
