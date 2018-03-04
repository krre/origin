extern crate serde_json;

use std::path::PathBuf;
use std::fs::File;
use std::io::{Write, Read, BufReader};
use std::env;

pub struct  Settings {
    settings_path: PathBuf,
    storage: serde_json::Value,
    is_loaded: bool
}

impl Settings {
    pub fn new() -> Self {
        // Get path to settings file
        let current_exe = env::current_exe().unwrap();
        let mut settings_path = current_exe.parent().unwrap().to_path_buf();
        settings_path.push("origin.ini");

        let mut storage = json!({});
        let mut is_loaded = false;

        // Read settings
        match File::open(&settings_path) {
            Ok(file) => {
                let mut buf = BufReader::new(file);
                let mut data = String::new();
                buf.read_to_string(&mut data).unwrap();

                storage = serde_json::from_str(data.as_str()).unwrap();
                is_loaded = true;
            },
            Err(_) => {}
        };

        Settings { settings_path, storage, is_loaded }
    }

    pub fn window_geometry(&self) -> (i32, i32, u32, u32) {
        if self.is_loaded {
            let x = self.storage["window"]["x"].as_i64().unwrap() as i32;
            let y = self.storage["window"]["y"].as_i64().unwrap() as i32;
            let width = self.storage["window"]["width"].as_i64().unwrap() as u32;
            let height = self.storage["window"]["height"].as_i64().unwrap() as u32;
            (x, y, width, height)
        } else {
            (i32::max_value(), i32::max_value(), u32::max_value(), u32::max_value())
        }
    }

    pub fn set_window_geometry(&mut self, x: i32, y: i32, width: u32, height: u32) {
        self.storage = json!({
            "window": {
                "x": x,
                "y": y,
                "width": width,
                "height": height
            }
        })
    }

    pub fn flush(&self) {
        let _file = File::create(&self.settings_path).unwrap().write_all(self.storage.to_string().as_bytes());
    }
}

impl Drop for Settings {
    fn drop(&mut self) {
        self.flush();
    }
}
