using System;
using System.Drawing;
using System.Collections;
using System.Windows.Forms;
using System.Data;
using System.Runtime.InteropServices;

namespace EgumaCppLibTester
{
	public class Form1 : System.Windows.Forms.Form
	{

		[DllImport("Eguma.dll")]
		public static extern bool GetBalance(byte[] apiKey, byte[] code, byte[] codeOut, out bool isRedeemable, out int balanceInCents, out Int32 totalAmountInCents, byte[] messageOut, byte[] error);

		[DllImport("Eguma.dll")]
		public static extern bool Redeem(byte[] apiKey, byte[] code, int amountInCents, byte[] codeOut, out int balanceInCents, byte[] error);

		[DllImport("Eguma.dll")]
		public static extern bool CancelRedemption(byte[] apiKey, byte[] code, int amountInCents, byte[] codeOut, out int balanceInCents, byte[] error);

		[DllImport("Eguma.dll")]
		public static extern bool DepotStatus(byte[] apiKey, byte[] code, out int amountInCents, out bool canBeActivated, out bool canBeDeactivated, byte[] codeOut, byte[] error);

		[DllImport("Eguma.dll")]
		public static extern bool Activate(byte[] apiKey, byte[] code, out int amountInCents, byte[] codeOut, byte[] error);

		[DllImport("Eguma.dll")]
		public static extern bool Deactivate(byte[] apiKey, byte[] code, out int amountInCents, byte[] codeOut, byte[] error);


		[DllImport("Eguma.dll")]
		public static extern bool Hello();

		

		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.Label labelCodeOut;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label labelIsRedeemable;
		private System.Windows.Forms.Label labelBalance;
		private System.Windows.Forms.Label labelMessage;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.Label labelTotalAmount;
		private System.Windows.Forms.Label labelXX;
		private System.Windows.Forms.Button button3;
		private System.Windows.Forms.Button button4;
		private System.Windows.Forms.Label labelRedeemBalanceInCents;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.Button button5;
		private System.Windows.Forms.Label labelCancelRedemptionBalanceInCents;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label labelDepotStatusAmountInCents;
		private System.Windows.Forms.Label label9;
		private System.Windows.Forms.Button button6;
		private System.Windows.Forms.Label labelDepotStatusIsInDepot;
		private System.Windows.Forms.Button button7;
		private System.Windows.Forms.Button button8;



		private System.Windows.Forms.Button button1;
	
		public Form1()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			base.Dispose( disposing );
		}
		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.button1 = new System.Windows.Forms.Button();
			this.button2 = new System.Windows.Forms.Button();
			this.labelCodeOut = new System.Windows.Forms.Label();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.labelIsRedeemable = new System.Windows.Forms.Label();
			this.labelBalance = new System.Windows.Forms.Label();
			this.labelTotalAmount = new System.Windows.Forms.Label();
			this.labelXX = new System.Windows.Forms.Label();
			this.labelMessage = new System.Windows.Forms.Label();
			this.label6 = new System.Windows.Forms.Label();
			this.button3 = new System.Windows.Forms.Button();
			this.button4 = new System.Windows.Forms.Button();
			this.labelRedeemBalanceInCents = new System.Windows.Forms.Label();
			this.label5 = new System.Windows.Forms.Label();
			this.button5 = new System.Windows.Forms.Button();
			this.labelCancelRedemptionBalanceInCents = new System.Windows.Forms.Label();
			this.label7 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.labelDepotStatusAmountInCents = new System.Windows.Forms.Label();
			this.label9 = new System.Windows.Forms.Label();
			this.labelDepotStatusIsInDepot = new System.Windows.Forms.Label();
			this.button6 = new System.Windows.Forms.Button();
			this.button7 = new System.Windows.Forms.Button();
			this.button8 = new System.Windows.Forms.Button();
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(56, 40);
			this.button1.Size = new System.Drawing.Size(200, 56);
			this.button1.Text = "Check Balance";
			this.button1.Click += new System.EventHandler(this.button1_Click);
			// 
			// button2
			// 
			this.button2.Location = new System.Drawing.Point(48, 408);
			this.button2.Size = new System.Drawing.Size(176, 64);
			this.button2.Text = "Close";
			this.button2.Click += new System.EventHandler(this.button2_Click);
			// 
			// labelCodeOut
			// 
			this.labelCodeOut.Location = new System.Drawing.Point(152, 136);
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(52, 136);
			this.label1.Text = "Code Out:";
			this.label1.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(-24, 160);
			this.label2.Size = new System.Drawing.Size(176, 24);
			this.label2.Text = "Balance (in Cents):";
			this.label2.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// label4
			// 
			this.label4.Location = new System.Drawing.Point(-24, 112);
			this.label4.Size = new System.Drawing.Size(176, 24);
			this.label4.Text = "Is Redeemable:";
			this.label4.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// labelIsRedeemable
			// 
			this.labelIsRedeemable.Location = new System.Drawing.Point(152, 112);
			// 
			// labelBalance
			// 
			this.labelBalance.Location = new System.Drawing.Point(152, 160);
			// 
			// labelTotalAmount
			// 
			this.labelTotalAmount.Location = new System.Drawing.Point(152, 184);
			// 
			// labelXX
			// 
			this.labelXX.Location = new System.Drawing.Point(-24, 184);
			this.labelXX.Size = new System.Drawing.Size(176, 24);
			this.labelXX.Text = "Total Amount (in Cents):";
			this.labelXX.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// labelMessage
			// 
			this.labelMessage.Location = new System.Drawing.Point(152, 208);
			this.labelMessage.Size = new System.Drawing.Size(392, 20);
			// 
			// label6
			// 
			this.label6.Location = new System.Drawing.Point(-24, 208);
			this.label6.Size = new System.Drawing.Size(176, 24);
			this.label6.Text = "Message:";
			this.label6.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// button3
			// 
			this.button3.Location = new System.Drawing.Point(688, 40);
			this.button3.Size = new System.Drawing.Size(144, 56);
			this.button3.Text = "Hello";
			this.button3.Click += new System.EventHandler(this.button3_Click);
			// 
			// button4
			// 
			this.button4.Location = new System.Drawing.Point(272, 40);
			this.button4.Size = new System.Drawing.Size(200, 56);
			this.button4.Text = "Redeem";
			this.button4.Click += new System.EventHandler(this.button4_Click_1);
			// 
			// labelRedeemBalanceInCents
			// 
			this.labelRedeemBalanceInCents.Location = new System.Drawing.Point(392, 112);
			this.labelRedeemBalanceInCents.Size = new System.Drawing.Size(80, 20);
			// 
			// label5
			// 
			this.label5.Location = new System.Drawing.Point(216, 112);
			this.label5.Size = new System.Drawing.Size(176, 24);
			this.label5.Text = "Balance (in Cents):";
			this.label5.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// button5
			// 
			this.button5.Location = new System.Drawing.Point(480, 40);
			this.button5.Size = new System.Drawing.Size(200, 56);
			this.button5.Text = "Cancel Redemption";
			this.button5.Click += new System.EventHandler(this.button5_Click);
			// 
			// labelCancelRedemptionBalanceInCents
			// 
			this.labelCancelRedemptionBalanceInCents.Location = new System.Drawing.Point(592, 112);
			// 
			// label7
			// 
			this.label7.Location = new System.Drawing.Point(480, 112);
			this.label7.Size = new System.Drawing.Size(112, 24);
			this.label7.Text = "Balance (in Cents):";
			this.label7.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(-32, 328);
			this.label3.Size = new System.Drawing.Size(176, 24);
			this.label3.Text = "Amount (in Cents):";
			this.label3.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// labelDepotStatusAmountInCents
			// 
			this.labelDepotStatusAmountInCents.Location = new System.Drawing.Point(152, 328);
			// 
			// label9
			// 
			this.label9.Location = new System.Drawing.Point(48, 352);
			this.label9.Text = "CanBeActivated:";
			this.label9.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// labelDepotStatusIsInDepot
			// 
			this.labelDepotStatusIsInDepot.Location = new System.Drawing.Point(152, 352);
			// 
			// button6
			// 
			this.button6.Location = new System.Drawing.Point(48, 256);
			this.button6.Size = new System.Drawing.Size(200, 56);
			this.button6.Text = "Depot Status";
			this.button6.Click += new System.EventHandler(this.button6_Click);
			// 
			// button7
			// 
			this.button7.Location = new System.Drawing.Point(280, 256);
			this.button7.Size = new System.Drawing.Size(200, 56);
			this.button7.Text = "Activate";
			this.button7.Click += new System.EventHandler(this.button7_Click);
			// 
			// button8
			// 
			this.button8.Location = new System.Drawing.Point(528, 256);
			this.button8.Size = new System.Drawing.Size(200, 56);
			this.button8.Text = "Deactivate";
			this.button8.Click += new System.EventHandler(this.button8_Click);
			// 
			// Form1
			// 
			this.ClientSize = new System.Drawing.Size(866, 479);
			this.Controls.Add(this.button8);
			this.Controls.Add(this.button7);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.labelDepotStatusAmountInCents);
			this.Controls.Add(this.label9);
			this.Controls.Add(this.labelDepotStatusIsInDepot);
			this.Controls.Add(this.button6);
			this.Controls.Add(this.labelCancelRedemptionBalanceInCents);
			this.Controls.Add(this.label7);
			this.Controls.Add(this.button5);
			this.Controls.Add(this.labelRedeemBalanceInCents);
			this.Controls.Add(this.label5);
			this.Controls.Add(this.button4);
			this.Controls.Add(this.button3);
			this.Controls.Add(this.labelMessage);
			this.Controls.Add(this.label6);
			this.Controls.Add(this.labelTotalAmount);
			this.Controls.Add(this.labelXX);
			this.Controls.Add(this.labelBalance);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.labelIsRedeemable);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.labelCodeOut);
			this.Controls.Add(this.button2);
			this.Controls.Add(this.button1);
			this.Text = "E-GUMA Win CE Tester";

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>

		static void Main() 
		{
			Application.Run(new Form1());
		}

		private void button1_Click(object sender, System.EventArgs e)
		{
			int balanceInCents;
			int totalAmount;
			byte[] codeOut = new byte[32];
			byte [] message = new byte[1024];
			byte[] error = new byte[1024];
			bool isRedeemable;

			GetBalance(System.Text.Encoding.ASCII.GetBytes("510e32c594d84816a4af9df0"), 
					   System.Text.Encoding.ASCII.GetBytes("2QH3-QTDM-28N6"),
					   codeOut,
					   out isRedeemable,
					   out balanceInCents,
					   out totalAmount,
					   message,
					   error);

			labelIsRedeemable.Text = isRedeemable ? "true" : "false";
			labelCodeOut.Text = System.Text.Encoding.ASCII.GetString(codeOut, 0, codeOut.Length);
			labelBalance.Text = balanceInCents.ToString();
			labelTotalAmount.Text = totalAmount.ToString();
			labelMessage.Text = System.Text.Encoding.ASCII.GetString(message, 0, message.Length);

			//MessageBox.Show("OK! Check out the file GetBalance.txt in the root directory");
		}

		private void button2_Click(object sender, System.EventArgs e)
		{
			Close();
		}

		private void button3_Click(object sender, System.EventArgs e)
		{
			if (Hello())
				MessageBox.Show("OK! Check out the file Hello.txt in the root directory");
			else
				MessageBox.Show("something went wrong...Check out the file Hello.txt in the root directory");

		}

		private void button4_Click_1(object sender, System.EventArgs e)
		{
			int balanceInCents;
			byte[] codeOut = new byte[32];
			byte[] error = new byte[1024];

			Redeem(System.Text.Encoding.ASCII.GetBytes("510e32c594d84816a4af9df0"), 
				System.Text.Encoding.ASCII.GetBytes("2QH3-QTDM-28N6"),
				200,
				codeOut,
				out balanceInCents,
				error);


			labelRedeemBalanceInCents.Text = balanceInCents.ToString();
		}

		private void button5_Click(object sender, System.EventArgs e)
		{
			
			int balanceInCents;
			byte[] codeOut = new byte[32];
			byte[] error = new byte[1024];

			CancelRedemption(System.Text.Encoding.ASCII.GetBytes("510e32c594d84816a4af9df0"), 
				System.Text.Encoding.ASCII.GetBytes("2QH3-QTDM-28N6"),
				200,
				codeOut,
				out balanceInCents,
				error);


			labelCancelRedemptionBalanceInCents.Text = balanceInCents.ToString();
		}

		private void button6_Click(object sender, System.EventArgs e)
		{
			int amountInCents;
			bool canBeActivated;
			bool canBeDeactivated;
			byte[] codeOut = new byte[32];
			byte[] error = new byte[1024];

			DepotStatus(System.Text.Encoding.ASCII.GetBytes("510e32c594d84816a4af9df0"), 
				System.Text.Encoding.ASCII.GetBytes("EADS-HD24-AKS5"),
				out amountInCents,
				out canBeDeactivated,
				out canBeActivated,
				codeOut,
				error);		

			labelDepotStatusAmountInCents.Text = amountInCents.ToString();
			labelDepotStatusIsInDepot.Text = canBeActivated ? "true" : "false";
		}

		private void button7_Click(object sender, System.EventArgs e)
		{
			int amountInCents;
			byte[] codeOut = new byte[32];
			byte[] error = new byte[1024];

			bool result = Activate(System.Text.Encoding.ASCII.GetBytes("510e32c594d84816a4af9df0"), 
				System.Text.Encoding.ASCII.GetBytes("EADS-HD24-AKS5"),
				out amountInCents,
				codeOut,
				error);		

			if (result)
				MessageBox.Show("The voucher has been activated.");
			else
				MessageBox.Show("Couldn't activate the voucher.");
			
		}

		private void button8_Click(object sender, System.EventArgs e)
		{
			
			int amountInCents;
			byte[] codeOut = new byte[32];
			byte[] error = new byte[1024];

			bool result = Deactivate(System.Text.Encoding.ASCII.GetBytes("510e32c594d84816a4af9df0"), 
				System.Text.Encoding.ASCII.GetBytes("EADS-HD24-AKS5"),
				out amountInCents,
				codeOut,
				error);		

			if (result)
				MessageBox.Show("The voucher has been deactivated.");
			else
				MessageBox.Show("Couldn't deactivate the voucher.");
		}
	}
}
