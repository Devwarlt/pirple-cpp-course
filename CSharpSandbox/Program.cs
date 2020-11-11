using System;

namespace CSharpSandbox
{
    public sealed class Program
    {
        private static void Main()
        {
            Console.Title = "C# Sandbox";

            module_7_bitwise_ops_tests();
        }

        private static void module_7_bitwise_ops_tests()
        {
            string bin_fmt(in int bin, in int str_size)
            {
                var str_ref = Convert.ToString(bin, 2).PadLeft(str_size, '0');
                return str_ref.Length <= str_size
                    ? str_ref
                    : str_ref.Remove(0, str_ref.Length - str_size);
            }
            string assert_bins_fmt(in int bin_from, in int bin_to, in int str_size)
            {
                var bin_from_str = bin_fmt(bin_from, str_size);
                var bin_to_str = bin_fmt(bin_to, str_size);
                return $"(valid: {bin_from_str}, equals? {bin_from_str.Equals(bin_to_str)})";
            }

            int bitset = 0b01110, right_shift_amount = 2, size = 5;
            var labels = new[] { "I", "II", "III", "IV", "V" };
            var bitsets = new[] { 0b01110, 0b10011, 0b11100, 0b00111, 0b11001 };
            var last_index = false;
            var index = 0;

            Console.WriteLine("Module 7 - Testing bitwise ops (right padding):\n");
            Console.WriteLine($"\t[{labels[0]}] -> {bin_fmt(bitset, size)} ({bin_fmt(bitsets[0], size)})");

            for (var i = 0; i < 5; i++)
            {
                bitwise_right_rotate(ref bitset, right_shift_amount, size);

                last_index = i + 1 == labels.Length;
                index = last_index ? 0 : i + 1;

                Console.WriteLine(
                    $"\t[{labels[index]}] -> {bin_fmt(bitset, size)}" +
                    $" {assert_bins_fmt(bitsets[index], bitset, size)}" +
                    $"{(last_index ? "" : $" (shift right +{right_shift_amount})")}"
                );
            }

            Console.WriteLine();
        }

        private static void bitwise_right_rotate(ref int bitset, in int right_shift_amount, in int size)
            => bitset = (bitset >> right_shift_amount) | (bitset << (size - right_shift_amount));
    }
}
