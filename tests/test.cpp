#include <gtest/gtest.h>

#include <Transaction.h>
#include <Account.h>

TEST(Account, balance){
Account a(1010203, 3400);
Account b(1012234, 100000);

EXPECT_EQ(a.GetBalance() + b.GetBalance(), 103400);

b.Lock();
b.ChangeBalance(50000);

EXPECT_EQ(b.GetBalance(), 150000);

}

TEST(Account, id){
Account a(12345, 999999);
Account b(23456, 1000000);

EXPECT_EQ(a.id(), 12345);
EXPECT_EQ(b.id(), 23456);
}

TEST(Account, lock){
Account a(333, 777);

EXPECT_ANY_THROW(a.ChangeBalance(333));
a.Lock();
EXPECT_ANY_THROW(a.Lock());
}

TEST(Transaction, fee){
  Account a(111, 5000);
  Account b(234, 0);
  Account c(345, 100);
  Transaction transaction;

  EXPECT_TRUE(transaction.Make(a, b, 1000));
  EXPECT_FALSE(transaction.Make(c, b, 100));
  c.Lock();
  c.ChangeBalance(-99);
  c.Unlock();
  EXPECT_FALSE(transaction.Make(c, a, 500));
  EXPECT_EQ(transaction.fee(), 1);
  transaction.set_fee(100);
  EXPECT_FALSE(transaction.Make(a, b, 199));
}

TEST(Transaction, exeptions){
    Account a(228, 1020);
    Account b(112, 27);
    Account c(228, 0);

    Transaction transaction;

 try {
        transaction.Make(a, b, 99);
        FAIL() << "expected std::logic_error";
    } catch (std::logic_error& error){
        std::cout << error.what() << '\n';
        EXPECT_EQ(error.what(), std::string("too small"));
    } catch (...){
        FAIL() << "expected std::logic_error";
    }
    try {
        transaction.Make(a, c, 1337);
        FAIL() << "expected std::logic_error";
    } catch (std::logic_error& error){
        std::cout << error.what() << '\n';
        EXPECT_EQ(error.what(), std::string("invalid action"));
    } catch (...){
        FAIL() << "expected std::logic_error";
    }

    try {
        transaction.Make(a, b, -55);
        FAIL() << "expected std::invalid_argument";
    } catch (std::invalid_argument& error){
        std::cout << error.what() << '\n';
        EXPECT_EQ(error.what(), std::string("sum can't be negative"));
    } catch (...){
        FAIL() << "expected std::invalid_argument";
    }
}
