# Strawberry Trading

A C++ options trading platform designed for paper trading and strategy development. This modular system provides real-time data processing, options chain analysis, and automated trading capabilities through the Alpaca API.

## 🏗️ Architecture

The project is organized into several modular components:

```
strawberry-trading/
├── api/              # HTTP client and API integration
├── apps/            # Applications (paper_trader)
├── core/            # Core trading logic and data structures
├── logging/         # Thread-safe logging system
├── scheduler/       # Task scheduling and timing
└── strategies/      # Trading strategies implementation
```

### Components

- **API Module**: HTTP client for Alpaca API integration with support for options data, market data, and order management
- **Core Module**: Options chain processing, Greeks calculations, and fundamental trading data structures
- **Logging Module**: Thread-safe singleton logger with file output and multiple log levels
- **Scheduler Module**: Task scheduling and timing utilities for trading operations
- **Strategies Module**: Trading strategy implementations and backtesting framework

## 🔧 Dependencies

### Required
- **CMake** 4.0.3+
- **C++20** compatible compiler
- **libcurl** - HTTP client library
- **nlohmann/json** 3.12.0+ - JSON parsing and serialization

### Installation (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install cmake build-essential libcurl4-openssl-dev
```

### Installation (macOS)
```bash
brew install cmake curl nlohmann-json
```

## 🚀 Building

### Clone and Build
```bash
git clone <repository-url>
cd strawberry-trading
mkdir build && cd build
cmake ..
make -j$(nproc)
```

### Build Output
Executables are generated in `build/bin/`:
- `paper_trader` - Main paper trading application

## 📊 Features

### Options Trading
- Real-time options chain processing
- Greeks calculations (Delta, Gamma, Vega, Theta, Rho)
- Implied volatility analysis
- Strike price and expiration filtering

### Market Data
- Real-time and historical stock/options bars
- Latest quote data
- Configurable timeframes
- Market data snapshots

### Order Management
- Market and limit orders
- Multiple order types (stop, stop-limit, trailing-stop)
- Time-in-force options (DAY, GTC, IOC, FOK)
- Order status tracking

### Risk Management
- Portfolio position tracking
- Real-time P&L calculations
- Risk metric monitoring

## 🔑 Configuration

### API Keys
Set your Alpaca API credentials as environment variables (.zshrc, .bashrc):
```bash
export ALPACA_API_KEY="your_api_key"
export ALPACA_SECRET_KEY="your_secret_key"
```

### Logging
Configure logging in your application:
```cpp
#include <logger_alias.hpp>

int main() {
    logger.set_log_file("trading.log");
    logger.info("Starting trading application");
    // Your trading logic here
}
```

## 📈 Usage Example

### Basic Options Chain Analysis
```cpp
#include <common/optionchain.hpp>
#include <logger_alias.hpp>

// Process options chain data from Alpaca
std::string chainData = api.getOptionChain("AAPL");
OptionChain chain(chainData);

// Extract Greeks
auto deltas = chain.get_deltas();
auto gammas = chain.get_gammas();

// Find specific option
Date expiry = Date::from_string("2024-01-19");
Option option = chain.find_Option("AAPL", expiry, 'C', 150.0);

logger.info("Found option: " + option.name);
```

### Paper Trading Application
```bash
cd build/bin
./paper_trader
```

## 🧪 Development

### Project Structure
- **Headers**: Located in `include/` directories within each module
- **Source**: Located in `src/` directories within each module
- **CMake**: Each module has its own `CMakeLists.txt`

### Adding New Strategies
1. Create strategy class in `strategies/src/`
2. Add corresponding header in `strategies/include/`
3. Implement required strategy interface methods
4. Register strategy in main application

### Testing
Build and run the paper trader application to test functionality:
```bash
make paper_trader
./bin/paper_trader
```

## 📋 API Coverage

### Market Data
- [x] Stock bars (historical/real-time)
- [x] Option bars (historical/real-time)
- [x] Latest quotes
- [x] Option chain snapshots
- [x] Greeks and implied volatility

### Trading
- [x] Order placement (market/limit)
- [x] Order status tracking
- [x] Portfolio positions
- [ ] Multi-leg option strategies
- [ ] Bracket orders

### Account
- [ ] Account information
- [ ] Balance tracking
- [ ] Trade history

## 🔒 Security

- API keys should never be committed to version control
- Use environment variables or secure configuration files
- Enable paper trading mode for development and testing

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🆘 Support

For questions and support:
- Open an issue on GitHub
- Check the documentation in the code comments
- Review the example applications in `apps/`
