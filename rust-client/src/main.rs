use std::env;
use std::time::Duration;

fn main() {
    let base = env::var("CPP_SERVICE_URL").unwrap_or_else(|_| "http://127.0.0.1:8080".into());
    let base = base.trim_end_matches('/').to_string();
    let url = format!("{base}/invoke");

    let client = reqwest::blocking::Client::builder()
        .timeout(Duration::from_secs(15))
        .build()
        .expect("http client");

    println!("polling {url} every 5s");

    loop {
        match client.get(&url).send() {
            Ok(resp) => {
                let status = resp.status();
                let body = resp.text().unwrap_or_default();
                println!("tick: status={status} body={body}");
            }
            Err(e) => eprintln!("request error: {e}"),
        }
        std::thread::sleep(Duration::from_secs(5));
    }
}
