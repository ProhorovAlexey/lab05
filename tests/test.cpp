#include <gtest/gtest.h>

#include <Transaction.h>
#include <Account.h>

TEST(Account, balance){
Account a(1010203, 3400);
Account b(1012234, 100000);

EXPECT_EQ(a.GetBalance(), 3400);
EXPECT_EQ(b.GetBalance(), 100000);

b.Lock();
b.ChangeBalance(50000);

EXPECT_EQ(b.GetBalance(), 150000);

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
